include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_PARAMETER_EVAL_ORDER = parameter_eval_order_bin
BIN_TAIL_RECURSION = tail_recursion_bin
BIN_NON_LOCAL_JMP = non_local_jmp_bin
BIN_VIRTUAL_FUNC = virtual_func_bin

# OBJ
OBJ_PARAMETER_EVAL_ORDER = parameter_eval_order.o
OBJ_TAIL_RECURSION = tail_recursion.o
OBJ_NON_LOCAL_JMP = non_local_jmp.o
OBJ_VIRTUAL_FUNC = virtual_func.o

INCLUDE = -I.
LIBPATH = -L.
LIBS =

# output
OUT_PUT = $(BIN_PARAMETER_EVAL_ORDER)\
			$(BIN_TAIL_RECURSION)\
			$(BIN_NON_LOCAL_JMP)\
			$(BIN_VIRTUAL_FUNC)

all:$(OUT_PUT)

$(BIN_PARAMETER_EVAL_ORDER): $(OBJ_PARAMETER_EVAL_ORDER)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_TAIL_RECURSION): $(OBJ_TAIL_RECURSION)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_NON_LOCAL_JMP): $(OBJ_NON_LOCAL_JMP)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

$(BIN_VIRTUAL_FUNC): $(OBJ_VIRTUAL_FUNC)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT) *.out