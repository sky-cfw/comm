# BIN
BIN_MMAP_FILE_IO = mmap_file_io_bin

# OBJ
OBJ_MMAP_FILE_IO = mmap_file_io.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MMAP_FILE_IO)

all:$(OUT_PUT)

$(BIN_MMAP_FILE_IO): $(OBJ_MMAP_FILE_IO)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)