include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_POINTER = pointer_bin 
BIN_POINTER_REFERENCE = pointer_reference_bin

# OBJ
OBJ_POINTER = pointer.o
OBJ_POINTER_REFERENCE = pointer_reference.o

INCLUDE = -I.
LIBPATH = 
LIBS = 

# output
OUT_PUT = $(BIN_POINTER) $(BIN_POINTER_REFERENCE)

all:$(OUT_PUT)

$(BIN_POINTER): $(OBJ_POINTER)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)
$(BIN_POINTER_REFERENCE): $(OBJ_POINTER_REFERENCE)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
