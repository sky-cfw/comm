#################### 测试=、:=、?=、+=的区别 ################
# 
HELLO = world

# =在执行时扩展(以HELLO最后一次定义为准)，允许递归扩展
ifeq ($(OP), equal)
	HELLO_WORLD = $(HELLO) world!
endif

# :=在定义时扩展
ifeq ($(OP), ce)
	HELLO_WORLD := $(HELLO) world!
endif

# ?=只有在变量为空时才设置值
ifeq ($(OP), qe)
	HELLO_WORLD ?= $(HELLO) world!
endif

all: target target1

# This echoes "world world!"
target:
	@echo $(HELLO_WORLD)

HELLO = hello

# This echoes "hello world!"
target1:
	@echo $(HELLO_WORLD)

