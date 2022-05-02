include $(COMM_BASE_PATH)/makefile.comm.v1

# BIN
BIN_DATA_TYPE_SIZE = data_type_size_bin

# OBJ
OBJ_DATA_TYPE_SIZE = data_type_size.o

%.o: %.cp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_DATA_TYPE_SIZE)

all:$(OUT_PUT)

$(BIN_DATA_TYPE_SIZE): $(OBJ_DATA_TYPE_SIZE)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)