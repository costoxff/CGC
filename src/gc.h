#ifndef __GARBAGE_COLLECTION_H__
#define __GARBAGE_COLLECTION_H__

#include <stddef.h>

void *gc_malloc(size_t size);
void *gc_realloc(void *ptr, size_t size);
void gc_free(void *ptr);

void gc_pool_free(void); // release
void gc_ptr_register(void *ptr); // mark
void gc_ptr_deregister(void *ptr);

#endif