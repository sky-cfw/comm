
# 编译器
CC = gcc
CXX = g++
RANLIB = ranlib
AR = ar

# 编译选项
# -Wall 打开所有可能的警告
# -g 使能gdb调试工具所需的调试信息
# -pg 使能gprof程序分析性能所需的profile信息
# -Wno-deprecated 已经废弃的特性不告警
CFLAGS = -Wall -g -O3 -pg --std=c++11 -Wno-deprecated

# .a静态库打包选项
# -c Create the archive. 表示创建一个静态库
# -r Insert the files member... into archive (with replacement). 表示将.o目标文件插入到静态库，如果有同名文件，则进行替换
# -l This modifier is accepted but not used. 这个修饰符暂时还未启用
ARFLAG = crl

# 目录定义
LIBS_DIR = $(COMM_BASE_PATH)/libs

# 自动生成目标文件
%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $< 

