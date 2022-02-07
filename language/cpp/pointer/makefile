# BIN
BIN_POINTER = pointer_bin 

# OBJ
OBJ_POINTER = pointer.o

%.o: %.cp
	$(CXX) $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_POINTER)

all:$(OUT_PUT)

$(BIN_POINTER): $(OBJ_POINTER)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)