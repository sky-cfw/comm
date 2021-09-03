# BIN
BIN_DECORATOR = decorator_bin

# OBJ
OBJ_DECORATOR = subject.o concrete_subject.o decorator.o client.o main.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_DECORATOR)

all:$(OUT_PUT)

$(BIN_DECORATOR): $(OBJ_DECORATOR)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)