# BIN
BIN_CLOSE_SHUTDOWN_CLIENT = close_shutdown_client
BIN_CLOSE_SHUTDOWN_SVR = close_shutdown_svr

# OBJ
OBJ_CLOSE_SHUTDOWN_CLIENT = close_shutdown_client.o
OBJ_CLOSE_SHUTDOWN_SVR = close_shutdown_svr.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_CLOSE_SHUTDOWN_CLIENT) $(BIN_CLOSE_SHUTDOWN_SVR)

all:$(OUT_PUT)

$(BIN_CLOSE_SHUTDOWN_CLIENT): $(OBJ_CLOSE_SHUTDOWN_CLIENT)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_CLOSE_SHUTDOWN_SVR): $(OBJ_CLOSE_SHUTDOWN_SVR)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)