#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/addrpool.h"

int main()
{
    struct address_pool *pool = NULL;
    address_pool_create(&pool);

    assert(pool != NULL);
    assert(pool->size == 0);
    assert(pool->capacity == ADDR_POOL_INIT_SIZE);
    assert(pool->addrs != NULL);


    int arr[63] = {};
    for (int i = 0; i < 63; i++) {
        address_pool_push(pool, (size_t)&arr[i]);
    }

    for (int i = 0; i < 63; i++) {
        printf("address: %p\n", (void *)address_pool_pop(pool, i));
    }
    
    address_pool_destroy(&pool);
    assert(pool == NULL);

    return 0;
}