include $(COMM_BASE_PATH)/makefile.comm.v1

# BIN
BIN_COMPILE_PROCESS = compile_process_bin

# OBJ
OBJ_COMPILE_PROCESS = compile_process.o

%.o: %.cp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_COMPILE_PROCESS)

all:$(OUT_PUT)

$(BIN_COMPILE_PROCESS): $(OBJ_COMPILE_PROCESS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)