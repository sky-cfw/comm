include $(COMM_BASE_PATH)/inc.v1.mk

CREATE_DIR = create_dir

# INC
INCLUDE = -I.

# LIB
LIBPATH = -L$(LIBS_DIR)
LIBS = -lpthread -lrt

# bin
BIN_MURMUR_HASH = libmurmur_hash3.a
BIN_HEAP = libheap.a
BIN_BLOOM_FILTER = libbloom_filter.a
BIN_TIME_WHEEL = libtime_wheel.a
# BIN_BLOOM_FILTER = bloom_filter
BIN_THREAD_LOCK = libthread_lock.a
BIN_PRINT_MEMORY_LAYOUT = libprint_memory_layout.a

# obj
OBJ_MURMUR_HASH = murmur_hash3.o
OBJ_HEAP = heap.o
OBJ_BLOOM_FILTER = bloom_filter.o
OBJ_TIME_WHEEL = time_wheel.o tlog.o
OBJ_THREAD_LOCK = thread_lock.o
OBJ_PRINT_MEMORY_LAYOUT = print_memory_layout.o

# output
OUT_PUT = $(BIN_MURMUR_HASH) \
		  $(BIN_HEAP) \
		  $(BIN_BLOOM_FILTER)\
		  $(BIN_TIME_WHEEL)\
		  $(BIN_THREAD_LOCK)\
		  $(BIN_PRINT_MEMORY_LAYOUT)


# 对于同名文件而言，无论是否指定 -f 选项，cp都会强制覆盖已存在同名文件
all: $(CREATE_DIR) $(OUT_PUT)
	cp -f $(OUT_PUT) $(LIBS_DIR) 

# test -d $(LIBS_DIR) || mkdir $(LIBS_DIR) 表示检查 LIBS_DIR 目录是否存在，如果不存在则执行第二个语句创建这个目录
create_dir:
	test -d $(LIBS_DIR) || mkdir $(LIBS_DIR)

$(BIN_MURMUR_HASH): $(OBJ_MURMUR_HASH)
	$(AR) $(ARFLAG) $@ $^

$(BIN_HEAP): $(OBJ_HEAP)
	$(AR) $(ARFLAG) $@ $^

$(BIN_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
	$(AR) $(ARFLAG) $@ $^

# $(BIN_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
# 	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(BIN_TIME_WHEEL): $(OBJ_TIME_WHEEL)
	$(AR) $(ARFLAG) $@ $^

$(BIN_THREAD_LOCK): $(OBJ_THREAD_LOCK)
	$(AR) $(ARFLAG) $@ $^

$(BIN_PRINT_MEMORY_LAYOUT): $(OBJ_PRINT_MEMORY_LAYOUT)
	$(AR) $(ARFLAG) $@ $^

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
