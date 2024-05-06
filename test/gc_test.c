#include "../src/gc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = gc_malloc(sizeof(int) * 3);

    p[0] = 1;
    p[1] = 5;
    p[2] = 10;

    for (int i = 0; i < 3; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");


    int *p1 = gc_malloc(sizeof(int) * 4);
    p1[0] = 2;
    p1[1] = 3;
    p1[2] = 5;
    p1[3] = 8;

    for (int i = 0; i < 4; i++) {
        printf("%d ", p1[i]);
    }
    printf("\n");

    // free(p);

    return 0;
}