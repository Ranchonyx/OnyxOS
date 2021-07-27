#ifndef __STDDEF_H__
#define __STDDEF_H__

#include "stdint.h"

#define XNULL ( (void*)0 )
#define xoffsetof(type, member) ( (size_t)&((type*)0)->member )

typedef intptr_t ptrdiff_t;
typedef uint32_t size_t;
typedef uint16_t wchar_t;

#endif