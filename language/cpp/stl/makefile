# BIN
BIN_VECTOR_CLEAR_MEMORY = vector_clear_memory_bin 

# OBJ
OBJ_VECTOR_CLEAR_MEMORY = vector_clear_memory.o

%.o: %.cp
	$(CXX) $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_VECTOR_CLEAR_MEMORY)

all:$(OUT_PUT)

$(BIN_VECTOR_CLEAR_MEMORY): $(OBJ_VECTOR_CLEAR_MEMORY)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)