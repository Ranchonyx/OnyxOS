#include "dmm.h"
#include "string.h"
#include "util.h"
#include "g_vga.h"

void init_dmm()
{
  dynmem_start = (dynmem_node_t *)DYNMEM_SZ;
  dynmem_start->sz = DYNMEM_SZ - DYNMEM_NODE_SZ;
  dynmem_start->next = XNULL;
  dynmem_start->prev = XNULL;
}

void *seek_best_mem_blk(dynmem_node_t *dynmem, size_t size)
{
  dynmem_node_t *best_mem_blk = (dynmem_node_t *) XNULL;
  uint32_t best_mem_blk_size = DYNMEM_SZ + 1;

  dynmem_node_t *current_mem_blk = dynmem;
  while(current_mem_blk) {
    if((!current_mem_blk->used) &&
      (current_mem_blk->sz >= (size + DYNMEM_NODE_SZ)) &&
      (current_mem_blk->sz <= best_mem_blk_size)) {

        best_mem_blk = current_mem_blk;
        best_mem_blk_size = current_mem_blk->sz;
      }

      current_mem_blk = current_mem_blk->next;
  }
  return best_mem_blk;
}

void *_malloc(size_t size)
{
  dynmem_node_t *best_mem_blk = (dynmem_node_t*) seek_best_mem_blk(dynmem_start, size);

  if(best_mem_blk != XNULL) {
    best_mem_blk->sz = best_mem_blk->sz - size - DYNMEM_NODE_SZ;

    dynmem_node_t *mem_node_allocate = (dynmem_node_t*) (((uint8_t*) best_mem_blk) + DYNMEM_NODE_SZ + best_mem_blk->sz);

    mem_node_allocate->sz = size;
    mem_node_allocate->used = true;
    mem_node_allocate->next = best_mem_blk->next;
    mem_node_allocate->prev = best_mem_blk;

    if(best_mem_blk->next != XNULL) {
      best_mem_blk->next->prev = mem_node_allocate;
    }
    best_mem_blk->next = mem_node_allocate;

    return (void*) ((uint8_t*) mem_node_allocate + DYNMEM_NODE_SZ);
  }
  return XNULL;
}

void* malloc(int n) {
    int *ptr = (int *) _malloc(n * sizeof(int));
    if (ptr == XNULL) {
        g_print_string("Memory not allocated.", 0x3, 0x0);
    }

    return ptr;
}

void free(void *p)
{
  if(p == XNULL) {
    return;
  }

  dynmem_node_t *current_mem_node = (dynmem_node_t*) ((uint8_t*) p - DYNMEM_NODE_SZ);

  if(current_mem_node == XNULL) {
    return;
  }

  current_mem_node->used = false;

  current_mem_node = mnnic(current_mem_node);
  mcnip(current_mem_node);
}


void *mnnic(dynmem_node_t *current_mem_node) {
    dynmem_node_t *next_mem_node = current_mem_node->next;
    if (next_mem_node != XNULL && !next_mem_node->used) {
        // add size of next block to current block
        current_mem_node->sz += current_mem_node->next->sz;
        current_mem_node->sz += DYNMEM_NODE_SZ;

        // remove next block from list
        current_mem_node->next = current_mem_node->next->next;
        if (current_mem_node->next != XNULL) {
            current_mem_node->next->prev = current_mem_node;
        }
    }
    return current_mem_node;
}

void *mcnip(dynmem_node_t *current_mem_node) {
    dynmem_node_t *prev_mem_node = current_mem_node->prev;
    if (prev_mem_node != XNULL && !prev_mem_node->used) {
        // add size of previous block to current block
        prev_mem_node->sz += current_mem_node->sz;
        prev_mem_node->sz += DYNMEM_NODE_SZ;

        // remove current node from list
        prev_mem_node->next = current_mem_node->next;
        if (current_mem_node->next != XNULL) {
            current_mem_node->next->prev = prev_mem_node;
        }
    }
}

void print_dynmem_node_sz()
{
  char s[256];
  itos(DYNMEM_NODE_SZ, s);
  g_t_print_string("DYNMEM_NODE_SZ = ", 0x3);
  g_t_print_string(s, 0x3);
}

void print_dynmem_node(dynmem_node_t *node)
{
  char s[256];
  itos(node->sz, s);
  g_t_print_string("[NODE{size = ", 0x3);
  g_t_print_string(s, 0x3);

  char u[256];
  itos(node->used, u);
  g_t_print_string("; used = ", 0x3);
  g_t_print_string(u, 0x3);
  g_t_print_string("}]", 0x3);
}

void print_dynmem()
{
  dynmem_node_t *current = dynmem_start;
  g_t_print_string("[", 0x3);
  while(current != XNULL) {
    print_dynmem_node(current);
    current = current->next;
  }
  g_t_print_string("]\n", 0x3);
}
