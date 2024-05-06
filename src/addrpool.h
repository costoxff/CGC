#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ADDR_POOL_INIT_SIZE 64UL

/*
 * use less 4 bit of address to record if the index of array is valid
*/
#define set_bit_invalid(addr) ((addr) |= 1UL)
#define set_bit_valid(addr) ((addr) &= (~0UL << 1))
#define get_bit_invalid(addr) ((addr) & 1UL)
#define get_real_addr(addr) ((addr) & (~0UL << 1)) // 64 bit address

struct address_pool {
    size_t size;
    size_t capacity;
    size_t *addrs;
};

static int address_pool_create(struct address_pool **pool);
static int address_pool_destroy(struct address_pool **pool);
static void address_pool_push(struct address_pool *pool, size_t addr);
static size_t address_pool_pop(struct address_pool *pool, size_t index);
static void address_pool_resize(struct address_pool *pool);

static inline int address_pool_empty(struct address_pool *pool);


static int address_pool_create(struct address_pool **pool)
{
    *pool = (struct address_pool *)malloc(sizeof(struct address_pool));
    (*pool)->size = 0;
    (*pool)->capacity = ADDR_POOL_INIT_SIZE;
    (*pool)->addrs = (size_t *)malloc(sizeof(size_t) * ADDR_POOL_INIT_SIZE);

    printf("address pool create, done\n");
    return 0;
}

static int address_pool_destroy(struct address_pool **pool)
{
    for (size_t i = 0; i < (*pool)->size; i++) {
        size_t addr = address_pool_pop(*pool, i);
        if (get_bit_invalid(addr))
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

    address_pool_resize(pool);

    set_bit_invalid(addr);
    for (size_t i = 0; i < pool->size; i++) {
        if (!get_bit_invalid(addrs[i])) {
            addrs[i] = addr;
            return;
        }
    }
    addrs[pool->size++] = addr;
}

static size_t address_pool_pop(struct address_pool *pool, size_t index)
{
    size_t *addrs = pool->addrs;

    set_bit_valid(addrs[index]);
    return get_real_addr(addrs[index]);
}

static void address_pool_resize(struct address_pool *pool)
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