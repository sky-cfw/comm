# INC
INCLUDE = -I${PLAT_COMM_PATH}/common/utils

# LIB
LIB = -lpthread -lrt

# bin
BIN_TIMER_TEST = timer_test
BIN_EPOLL_TIMER = epoll_timer

# obj
OBJ_TIMER_TEST = timer_test.o
OBJ_EPOLL_TIMER = epoll_timer.o reactor.o

VPATH=../utils/

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $^ -Wno-deprecated

# output
OUT_PUT = $(BIN_TIMER_TEST) $(BIN_EPOLL_TIMER)

all:$(OUT_PUT)

$(BIN_TIMER_TEST): $(OBJ_TIMER_TEST)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_EPOLL_TIMER): $(OBJ_EPOLL_TIMER)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated


clean:
	rm -f *.o $(OUT_PUT)

.PHONY: clean all
