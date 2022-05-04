include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_DATA_TYPE_SIZE = data_type_size_bin
BIN_EMPTY_CLASS = empty_class_bin
BIN_TYPE_CAST = type_cast_bin

# OBJ
OBJ_DATA_TYPE_SIZE = data_type_size.o
OBJ_EMPTY_CLASS = empty_class.o
OBJ_TYPE_CAST = type_cast.o

INCLUDE = -I. -I$(COMM_BASE_PATH)/utils
LIBPATH = -L$(LIBS_DIR)
LIBS = -lprint_memory_layout

# output
OUT_PUT = $(BIN_DATA_TYPE_SIZE) $(BIN_EMPTY_CLASS) $(BIN_TYPE_CAST)

all:$(OUT_PUT)

$(BIN_DATA_TYPE_SIZE): $(OBJ_DATA_TYPE_SIZE)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_EMPTY_CLASS): $(OBJ_EMPTY_CLASS)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_TYPE_CAST): $(OBJ_TYPE_CAST)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT) *.out