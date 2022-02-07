# BIN
BIN_PARAMETER_EVAL_ORDER = parameter_eval_order_bin
BIN_TAIL_RECURSION = tail_recursion_bin
BIN_NON_LOCAL_JMP = non_local_jmp_bin

# OBJ
OBJ_PARAMETER_EVAL_ORDER = parameter_eval_order.o
OBJ_TAIL_RECURSION = tail_recursion.o
OBJ_NON_LOCAL_JMP = non_local_jmp.o

%.o: %.cp
	g++ $(INCLUDE) -c -o $@ $< -Wno-deprecated

# output
OUT_PUT = $(BIN_PARAMETER_EVAL_ORDER) $(BIN_TAIL_RECURSION) $(BIN_NON_LOCAL_JMP)

all:$(OUT_PUT)

$(BIN_PARAMETER_EVAL_ORDER): $(OBJ_PARAMETER_EVAL_ORDER)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TAIL_RECURSION): $(OBJ_TAIL_RECURSION)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_NON_LOCAL_JMP): $(OBJ_NON_LOCAL_JMP)
	g++ -Wall -g -o $@ $^ $(LIB) -Wno-deprecated

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)