# BIN
BIN_MALLOC = malloc_bin

# OBJ
OBJ_MALLOC = malloc.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MALLOC)

all:$(OUT_PUT)

$(BIN_MALLOC): $(OBJ_MALLOC)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)