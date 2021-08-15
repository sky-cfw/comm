include ../inc.mk

# bin
BIN_MAX_THREAD_NUM = max_thread_num 
BIN_MAX_PROCESS_NUM = max_process_num
BIN_FORK_AND_IO = fork_and_io

# obj
OBJ_MAX_THREAD_NUM = max_thread_num.o 
OBJ_MAX_PROCESS_NUM = max_process_num.o
OBJ_FORK_AND_IO = fork_and_io.o

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MAX_THREAD_NUM) $(BIN_MAX_PROCESS_NUM) $(BIN_FORK_AND_IO)

all:$(OUT_PUT)

$(BIN_MAX_THREAD_NUM): $(OBJ_MAX_THREAD_NUM)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_MAX_PROCESS_NUM): $(OBJ_MAX_PROCESS_NUM)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_FORK_AND_IO): $(OBJ_FORK_AND_IO)
	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
