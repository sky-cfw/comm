include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_POINTER = pointer_bin 

# OBJ
OBJ_POINTER = pointer.o

INCLUDE = -I.
LIBPATH = 
LIBS = 

# output
OUT_PUT = $(BIN_POINTER)

all:$(OUT_PUT)

$(BIN_POINTER): $(OBJ_POINTER)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
