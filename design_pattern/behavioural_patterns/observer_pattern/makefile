# BIN
BIN_OBSERVER_PATTERN = observer_pattern_bin

# OBJ
OBJ_OBSERVER_PATTERN = subject.o observer.o concrete_subject.o concrete_observer.o main.o

%.o: %.cpp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_OBSERVER_PATTERN)

all:$(OUT_PUT)

$(BIN_OBSERVER_PATTERN): $(OBJ_OBSERVER_PATTERN)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated


.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)