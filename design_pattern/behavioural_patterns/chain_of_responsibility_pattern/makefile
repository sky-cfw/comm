# BIN
BIN_CHAIN_OF_RESPONSIBILITY = chain_of_responsibility_bin

# OBJ
OBJ_CHAIN_OF_RESPONSIBILITY = handler.o concrete_handler.o client.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_CHAIN_OF_RESPONSIBILITY)

all:$(OUT_PUT)

$(BIN_CHAIN_OF_RESPONSIBILITY): $(OBJ_CHAIN_OF_RESPONSIBILITY)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)