include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_DATA_TYPE_SIZE = data_type_size_bin
BIN_EMPTY_CLASS = empty_class_bin

# OBJ
OBJ_DATA_TYPE_SIZE = data_type_size.o
OBJ_EMPTY_CLASS = empty_class.o

INCLUDE = 
LIBPATH = 
LIBS = 

# output
OUT_PUT = $(BIN_DATA_TYPE_SIZE) $(BIN_EMPTY_CLASS)

all:$(OUT_PUT)

$(BIN_DATA_TYPE_SIZE): $(OBJ_DATA_TYPE_SIZE)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_EMPTY_CLASS): $(OBJ_EMPTY_CLASS)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)