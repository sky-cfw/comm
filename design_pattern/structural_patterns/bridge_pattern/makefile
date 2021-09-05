# BIN
BIN_BRIDGE = bridge_bin

# OBJ
OBJ_BRIDGE = abstraction.o refined_abstraction.o implementor.o concrete_implementor.o client.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_BRIDGE)

all:$(OUT_PUT)

$(BIN_BRIDGE): $(OBJ_BRIDGE)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)