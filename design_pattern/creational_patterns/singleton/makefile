# BIN
BIN_HUNGRY_SINGLETON = hungry_singleton_bin
BIN_LAZY_SINGLETON = lazy_singleton_bin

# OBJ
OBJ_HUNGRY_SINGLETON = hungry_singleton.o
OBJ_LAZY_SINGLETON = lazy_singleton.o

%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_HUNGRY_SINGLETON) $(BIN_LAZY_SINGLETON)

all:$(OUT_PUT)

$(BIN_HUNGRY_SINGLETON): $(OBJ_HUNGRY_SINGLETON)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated
$(BIN_LAZY_SINGLETON): $(OBJ_LAZY_SINGLETON)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)