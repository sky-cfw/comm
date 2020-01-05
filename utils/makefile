# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt

# bin
BIN_MURMUR_HASH = libmurmur_hash3.a


# obj
OBJ_MURMUR_HASH = murmur_hash3.o


VPATH=.

#
%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MURMUR_HASH)

all:$(OUT_PUT)
	cp $(OUT_PUT) ../libs/

$(BIN_MURMUR_HASH): $(OBJ_MURMUR_HASH)
	ar -crl $@ $^

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
