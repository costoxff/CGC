CC ?= gcc
CFLAGS = -g -Wall

SRC = ../src/
INC = ../src/

GC_TEST_DEP = $(addprefix $(SRC), gc.c gc.h addrpool.h)

gc_test: gc_test.c
	$(CC) $(CFLAGS) $^ -o $@

POOL_TEST_DEP = $(addprefix $(SRC), addrpool.h)

pool_func_test: pool_func_test.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf gc_test
	rm -rf pool_func_test