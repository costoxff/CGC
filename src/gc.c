#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "gc.h"
#include "addrpool.h"

static struct address_pool *obj_pool = NULL;
// static void **addr_pool = NULL;
// static unsigned int addr_idx = 0;

void *gc_malloc(size_t size)
{
    void *ptr = malloc(size);

    static int first_process = 1;
    if (first_process) {
        atexit(gc_pool_free);
        address_pool_create(&obj_pool);
        first_process = 0;
    }
    gc_ptr_register(ptr);

    printf("gc_malloc %ld done\n", obj_pool->size);
    return ptr;
}

void *gc_realloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);

    if (!ret) {
        fprintf(stderr, "gc realloc failed");
        assert(0);
    }

    if (ret != ptr) {
        gc_ptr_deregister(ptr); // deregister
        gc_ptr_register(ret);
    }

    return ret;
}

void gc_free(void *ptr)
{
    gc_ptr_deregister(ptr);
    free(ptr);
}

void gc_pool_free(void)
{
    address_pool_destroy(&obj_pool);
}

void gc_ptr_register(void *ptr)
{
    address_pool_push(obj_pool, (size_t)ptr);

    printf("address: %p has been add to pool\n", ptr);
}

void gc_ptr_deregister(void *ptr)
{
    size_t addr = (size_t)ptr;
    size_t *addrs = obj_pool->addrs;
    size_t i = 0;

    // TODO: find a way to search in O(1)
    for (i = 0; i < obj_pool->size; i++) {
        if(addr_valid(addr) && addr == addrs[i]) {
            break;
        }
    }
    address_pool_pop(obj_pool, i);
}