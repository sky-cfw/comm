# BIN
BIN_DIFFERENCE_MALLOC_NEW = difference_malloc_new_bin

# OBJ
OBJ_DIFFERENCE_MALLOC_NEW = difference_malloc_new.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_DIFFERENCE_MALLOC_NEW)

all:$(OUT_PUT)

$(BIN_DIFFERENCE_MALLOC_NEW): $(OBJ_DIFFERENCE_MALLOC_NEW)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)