# BIN
BIN_MAIN_V1 = main_v1
BIN_MAIN_V2 = main_v2
BIN_MAIN_V3 = main_v3
BIN_MAIN_V4 = main_v4

# OBJ
OBJ_MAIN_V1 = factory_method.o main_v1.o
OBJ_MAIN_V2 = factory_method.o main_v2.o
OBJ_MAIN_V3 = factory_method.o main_v3.o
OBJ_MAIN_V4 = factory_method.o main_v4.o

%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_MAIN_V1) $(BIN_MAIN_V2) $(BIN_MAIN_V3) $(BIN_MAIN_V4)

all:$(OUT_PUT)

$(BIN_MAIN_V1): $(OBJ_MAIN_V1)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated
$(BIN_MAIN_V2): $(OBJ_MAIN_V2)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated
$(BIN_MAIN_V3): $(OBJ_MAIN_V3)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated
$(BIN_MAIN_V4): $(OBJ_MAIN_V4)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)