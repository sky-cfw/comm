# BIN
BIN_TEMPLATE_METHOD = template_method_bin

# OBJ
OBJ_TEMPLATE_METHOD = abstract.o concrete1.o concrete2.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_TEMPLATE_METHOD)

all:$(OUT_PUT)

$(BIN_TEMPLATE_METHOD): $(OBJ_TEMPLATE_METHOD)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)