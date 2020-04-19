# FLAGS
CXXFLAGS = -Wall -g -fPIC -pg -std=c++11

# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt \
-L$(PLAT_COMM_PATH)/comm/libs -lmurmur_hash3 -lheap

# bin
BIN_TEST_KILL_SIG_0 = test_kill_sig_0

# obj
OBJ_TEST_KILL_SIG_0 = test_kill_sig_0.o

VPATH=../utils/:performance/:leetcode/:leetcode/hash/:leetcode/heap/:leetcode/graph:leetcode/string_match:leetcode/greedy

#
%.o: %.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

# output
OUT_PUT = $(BIN_TEST_KILL_SIG_0) 

all:$(OUT_PUT)

$(BIN_KILL_SIG_0): $(OBJ_KILL_SIG_0)
	g++ $(CXXFLAGS) -o $@ $^ 

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
