# BIN
BIN_STATIC_PROXY = static_proxy_bin

# OBJ
OBJ_STATIC_PROXY = subject.o real_subject.o proxy.o client.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_STATIC_PROXY)

all:$(OUT_PUT)

$(BIN_STATIC_PROXY): $(OBJ_STATIC_PROXY)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)