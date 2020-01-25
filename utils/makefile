# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt

# bin
BIN_MURMUR_HASH = libmurmur_hash3.a
BIN_HEAP = libheap.a

# obj
OBJ_MURMUR_HASH = murmur_hash3.o
OBJ_HEAP = heap.o

VPATH=.:../test/leetcode/heap

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MURMUR_HASH) $(BIN_HEAP)

all:$(OUT_PUT)
	cp $(OUT_PUT) ../libs/

$(BIN_MURMUR_HASH): $(OBJ_MURMUR_HASH)
	ar -crl $@ $^

$(BIN_HEAP): $(OBJ_HEAP)
	ar -crl $@ $^

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
