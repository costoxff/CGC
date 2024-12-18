#ifndef CGC_ADDRPOOL_H
#define CGC_ADDRPOOL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ADDR_POOL_INIT_SIZE 64UL
#define NULL_ADDR 0UL

#define addr_valid(addr) ((addr) != NULL_ADDR)
#define addr_invalid(addr) ((addr) == NULL_ADDR)

/*
 * use less 4 bit of address to record if the index of array is valid
*/
// #define set_bit_invalid(addr) ((addr) |= 1UL)
// #define set_bit_valid(addr) ((addr) &= (~0UL << 1))
// #define get_bit_invalid(addr) ((addr) & 1UL)
// #define get_real_addr(addr) ((addr) & (~0UL << 1)) // 64 bit address

struct address_pool {
    size_t size;
    size_t capacity;
    size_t *addrs;
};

static int address_pool_create(struct address_pool **pool);
static int address_pool_destroy(struct address_pool **pool);
static void address_pool_push(struct address_pool *pool, size_t addr);
static size_t address_pool_pop(struct address_pool *pool, size_t index);
static void _address_pool_resize(struct address_pool *pool);

static inline int address_pool_empty(struct address_pool *pool);


static int address_pool_create(struct address_pool **pool)
{
    *pool = (struct address_pool *) malloc(sizeof(struct address_pool));
    (*pool)->size = 0;
    (*pool)->capacity = ADDR_POOL_INIT_SIZE;
    (*pool)->addrs = (size_t *)calloc(ADDR_POOL_INIT_SIZE, sizeof(size_t));

    printf("address pool create, done\n");
    return 0;
}

static int address_pool_destroy(struct address_pool **pool)
{
    for (size_t i = 0; i < (*pool)->size; i++) {
        size_t addr = address_pool_pop(*pool, i);
        if (addr_valid(addr))
            free((void *)addr);
    }
    free((*pool)->addrs);
    free(*pool);

    pool = NULL;
    printf("address pool destroy, done\n");
    return 0;
}

static void address_pool_push(struct address_pool *pool, size_t addr)
{
    size_t *addrs = pool->addrs;

    _address_pool_resize(pool);

    for (size_t i = 0; i < pool->size; i++) {
        if (addr_valid(addr)) {
            addrs[i] = addr;
            return;
        }
    }
    addrs[pool->size++] = addr;
}

static size_t address_pool_pop(struct address_pool *pool, size_t index)
{
    size_t *addrs = pool->addrs, ret_addr;

    ret_addr = addrs[index];
    addrs[index] = NULL_ADDR;
    return ret_addr;
}

static void _address_pool_resize(struct address_pool *pool)
{
    size_t size = pool->size;
    size_t capacity = pool->capacity;
    size_t *addrs = pool->addrs;
    
    int last_capacity = capacity - size;
    if (last_capacity < sizeof(void *)) {
        return;
    }

    size_t new_capacity = capacity * 2;
    size_t *new_addrs = (size_t *)reallocarray(addrs, new_capacity, sizeof(size_t));

    if (!new_addrs) {
        fprintf(stderr, "realloc address pool failed");
        assert(0);
    }

    pool->capacity = new_capacity;
    pool->addrs = new_addrs;
}

static inline int address_pool_empty(struct address_pool *pool)
{
    return pool->size == 0;
}

#endif