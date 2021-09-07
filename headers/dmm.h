#ifndef DMM_H
#define DMM_H
#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
//Heavily based upon FrOS DMM
//Uses doubly-linked-list

#define MEMORY_KB       1024
#define DYNMEM_NODE_SZ  sizeof(dynmem_node_t)
#define DYNMEM_SZ       (32 * MEMORY_KB)


typedef struct dynmem_node {
  uint32_t sz;
  bool used;
  struct dynmem_node *next;
  struct dynmem_node *prev;
} dynmem_node_t;

static uint8_t dynmem_area[DYNMEM_SZ];
static dynmem_node_t *dynmem_start;



void    init_dmm();
void    *seek_best_mem_blk(dynmem_node_t *dynmem, size_t size);
void    free(void *p);
void    *_malloc(size_t size);
void    *malloc(int n);
void    *mnnic(dynmem_node_t *current_mem_node);
void    *mcnip(dynmem_node_t *current_mem_node);
void    print_dynmem_node_sz();
void    print_dynmem_node(dynmem_node_t *node);
void    print_dynmem();
#endif /* end of include guard: DMM_H */
