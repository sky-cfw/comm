# BIN
BIN_ADAPTER_PATTERN = adapter_pattern_bin

# OBJ
OBJ_ADAPTER_PATTERN = adaptee.o adapter.o target.o client.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_ADAPTER_PATTERN)

all:$(OUT_PUT)

$(BIN_ADAPTER_PATTERN): $(OBJ_ADAPTER_PATTERN)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)