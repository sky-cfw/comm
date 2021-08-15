# BIN
BIN_STRATEGY_PATTERN = strategy_pattern_bin

# OBJ
OBJ_STRATEGY_PATTERN = strategy.o concrete_strategy1.o concrete_strategy2.o context.o main.o

%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_STRATEGY_PATTERN)

all:$(OUT_PUT)

$(BIN_STRATEGY_PATTERN): $(OBJ_STRATEGY_PATTERN)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)