# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt

# bin
BIN_TIMER_TEST = timer_test
BIN_EPOLL_TIMER = epoll_timer
BIN_TEST_THUNDERING_HERD = test_thundering_herd

# obj
OBJ_TIMER_TEST = timer_test.o
OBJ_EPOLL_TIMER = epoll_timer.o reactor.o
OBJ_TEST_THUNDERING_HERD = test_thundering_herd.o

VPATH=../utils/

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_TIMER_TEST) $(BIN_EPOLL_TIMER) $(BIN_TEST_THUNDERING_HERD) 

all:$(OUT_PUT)

$(BIN_TIMER_TEST): $(OBJ_TIMER_TEST)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_EPOLL_TIMER): $(OBJ_EPOLL_TIMER)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TEST_THUNDERING_HERD): $(OBJ_TEST_THUNDERING_HERD)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
