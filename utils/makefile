include $(COMM_BASE_PATH)/inc.v1.mk

CREATE_DIR = create_dir

# INC
INCLUDE = -I.

# LIB
LIBPATH = -L$(LIBS_DIR)
LIBS = -lpthread -lrt

# lib
LIB_UTILS = libutils.a
LIB_MURMUR_HASH = libmurmur_hash3.a
LIB_HEAP = libheap.a
LIB_BLOOM_FILTER = libbloom_filter.a
LIB_TIME_WHEEL = libtime_wheel.a
# LIB_BLOOM_FILTER = bloom_filter
LIB_THREAD_LOCK = libthread_lock.a
LIB_PRINT_MEMORY_LAYOUT = libprint_memory_layout.a
LIB_RAPIDJSON_TOOLS = librapidjson_tools.a

# obj
OBJ_UTILS = tlog.o print_memory_layout.o murmur_hash3.o
OBJ_MURMUR_HASH = murmur_hash3.o
OBJ_HEAP = heap.o
OBJ_BLOOM_FILTER = bloom_filter.o
OBJ_TIME_WHEEL = time_wheel.o tlog.o
OBJ_THREAD_LOCK = thread_lock.o
OBJ_PRINT_MEMORY_LAYOUT = print_memory_layout.o
OBJ_RAPIDJSON_TOOLS = rapidjson_tools.o

# output
OUT_PUT = $(LIB_UTILS)\
		  $(LIB_MURMUR_HASH) \
		  $(LIB_HEAP) \
		  $(LIB_BLOOM_FILTER)\
		  $(LIB_TIME_WHEEL)\
		  $(LIB_THREAD_LOCK)\
		  $(LIB_PRINT_MEMORY_LAYOUT)\
		  $(LIB_RAPIDJSON_TOOLS)


# 对于同名文件而言，无论是否指定 -f 选项，cp都会强制覆盖已存在同名文件
all: $(CREATE_DIR) $(OUT_PUT)
	cp -f $(OUT_PUT) $(LIBS_DIR)

install: all
	make clean	

# test -d $(LIBS_DIR) || mkdir $(LIBS_DIR) 表示检查 LIBS_DIR 目录是否存在，如果不存在则执行第二个语句创建这个目录
create_dir:
	test -d $(LIBS_DIR) || mkdir $(LIBS_DIR)

$(LIB_UTILS): $(OBJ_UTILS)
	$(AR) $(ARFLAG) $@ $^

$(LIB_MURMUR_HASH): $(OBJ_MURMUR_HASH)
	$(AR) $(ARFLAG) $@ $^

$(LIB_HEAP): $(OBJ_HEAP)
	$(AR) $(ARFLAG) $@ $^

$(LIB_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
	$(AR) $(ARFLAG) $@ $^

# $(LIB_BLOOM_FILTER): $(OBJ_BLOOM_FILTER)
# 	g++ -Wall -g -fPIC -o $@ $^ $(LIB) -Wno-deprecated

$(LIB_TIME_WHEEL): $(OBJ_TIME_WHEEL)
	$(AR) $(ARFLAG) $@ $^

$(LIB_THREAD_LOCK): $(OBJ_THREAD_LOCK)
	$(AR) $(ARFLAG) $@ $^

$(LIB_PRINT_MEMORY_LAYOUT): $(OBJ_PRINT_MEMORY_LAYOUT)
	$(AR) $(ARFLAG) $@ $^

$(LIB_RAPIDJSON_TOOLS): $(OBJ_RAPIDJSON_TOOLS)
	$(AR) $(ARFLAG) $@ $^

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT)
