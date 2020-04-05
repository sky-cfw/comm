# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt \
-L$(PLAT_COMM_PATH)/comm/libs -lmurmur_hash3 -lheap

# bin
BIN_MURMUR_HASH = libmurmur_hash3.a
BIN_HEAP = libheap.a
BIN_BLOOM_FILTER = libbloom_filter.a
# BIN_BLOOM_FILTER = bloom_filter

# obj
OBJ_MURMUR_HASH = murmur_hash3.o
OBJ_HEAP = heap.o
OBJ_BLOOM_FILTER = bloom_filter.o

VPATH=.:../test/leetcode/heap

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MURMUR_HASH) \
		  $(BIN_HEAP) \
		  $(BIN_BLOOM_FILTER)

all:$(OUT_PUT)
	cp $(OUT_PUT) ../libs/

$(BIN_MURMUR_HASH): $(OBJ_MURMUR_HASH)
	ar -crl $@ $^

$(BIN_HEAP): $(OBJ_HEAP)
	ar -crl $@ $^

$(BIN_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
	ar -crl $@ $^

# $(BIN_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
# 	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
