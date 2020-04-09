# FLAGS
CXXFLAGS = -Wall -g -fPIC -shared -pg -std=c++11

# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt \
-L$(PLAT_COMM_PATH)/comm/libs -lmurmur_hash3 -lheap

# bin
BIN_HELLO = libhello.so.3.0.0

# obj
OBJ_HELLO = hello.o

VPATH=../utils/:performance/:leetcode/:leetcode/hash/:leetcode/heap/:leetcode/graph:leetcode/string_match:leetcode/greedy

#
%.o: %.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

# output
OUT_PUT = $(BIN_HELLO) 

all:$(OUT_PUT)

$(BIN_HELLO): $(OBJ_HELLO)
	g++ $(CXXFLAGS) -Wl,-soname,libhello.so.3 -o $@ $^ 

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
