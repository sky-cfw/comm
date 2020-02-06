# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt \
-L$(PLAT_COMM_PATH)/comm/libs -lmurmur_hash3 -lheap

# bin
BIN_TIMER_TEST = timer_test
BIN_EPOLL_TIMER = epoll_timer
BIN_TEST_THUNDERING_HERD = test_thundering_herd
BIN_TEST_SET_SOCK_OPT = test_set_sock_opt
BIN_TEST_TCP_NAGLE_CLIENT = test_tcp_nagle_client
BIN_TEST_CMP_COST = test_cmp_cost
BIN_MY_SQRT = my_sqrt
BIN_CONSISTENT_HASH = consistent_hash
BIN_PERCENT = percent
BIN_BFS = bfs
BIN_DFS = dfs
BIN_BM = bm

# obj
OBJ_TIMER_TEST = timer_test.o
OBJ_EPOLL_TIMER = epoll_timer.o reactor.o
OBJ_TEST_THUNDERING_HERD = test_thundering_herd.o nonblockio.o
OBJ_TEST_SET_SOCK_OPT = test_set_sock_opt.o
OBJ_TEST_TCP_NAGLE_CLIENT = test_tcp_nagle_client.o
OBJ_TEST_CMP_COST = test_cmp_cost.o
OBJ_MY_SQRT = sqrt.o
OBJ_CONSISTENT_HASH = consistent_hash.o
OBJ_PERCENT = percent.o
OBJ_BFS = bfs.o
OBJ_DFS = dfs.o
OBJ_BM = bm.o

VPATH=../utils/:performance/:leetcode/:leetcode/hash/:leetcode/heap/:leetcode/graph:leetcode/string_match

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_TIMER_TEST) \
$(BIN_EPOLL_TIMER) \
$(BIN_TEST_THUNDERING_HERD) \
$(BIN_TEST_SET_SOCK_OPT) \
$(BIN_TEST_TCP_NAGLE_CLIENT) \
$(BIN_TEST_CMP_COST) \
$(BIN_MY_SQRT)\
$(BIN_CONSISTENT_HASH)\
$(BIN_PERCENT)\
$(BIN_BFS)\
$(BIN_DFS)\
$(BIN_BM)

all:$(OUT_PUT)

$(BIN_TIMER_TEST): $(OBJ_TIMER_TEST)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_EPOLL_TIMER): $(OBJ_EPOLL_TIMER)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TEST_THUNDERING_HERD): $(OBJ_TEST_THUNDERING_HERD)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TEST_SET_SOCK_OPT): $(OBJ_TEST_SET_SOCK_OPT)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TEST_TCP_NAGLE_CLIENT): $(OBJ_TEST_TCP_NAGLE_CLIENT)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TEST_CMP_COST): $(OBJ_TEST_CMP_COST)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated	

$(BIN_MY_SQRT): $(OBJ_MY_SQRT)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated	

$(BIN_CONSISTENT_HASH): $(OBJ_CONSISTENT_HASH)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated	

$(BIN_PERCENT): $(OBJ_PERCENT)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_BFS): $(OBJ_BFS)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_DFS): $(OBJ_DFS)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_BM): $(OBJ_BM)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
