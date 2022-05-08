include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_COMPILE_PROCESS = compile_process_bin
BIN_COMPILE_TEMPLATE = compile_template_bin

# OBJ
OBJ_COMPILE_PROCESS = compile_process.o
OBJ_COMPILE_TEMPLATE =  test_compile_template.o# template_use1.o template_use2.o

# VPATH环境变量用于指定编译器搜索文件(源文件和目标文件)的目录，多个以空格分隔
# 搜索都是先从makefile当前目录然后再从VPATH环境变量指定的目录搜索
VPATH = compile_template

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

# output
OUT_PUT = $(BIN_COMPILE_PROCESS) $(BIN_COMPILE_TEMPLATE)

all:$(OUT_PUT)

$(BIN_COMPILE_PROCESS): $(OBJ_COMPILE_PROCESS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

$(BIN_COMPILE_TEMPLATE): $(OBJ_COMPILE_TEMPLATE)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT) *.out