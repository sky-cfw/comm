# env var
PLAT_COMM_PATH=/home/sky/

# INC
INCLUDE = -I${PLAT_COMM_PATH}/comm/utils

# LIB
LIB = -lpthread -lrt \
-L$(PLAT_COMM_PATH)/comm/libs -lmurmur_hash3 -lheap -ltime_wheel

VPATH=../utils/:performance/:leetcode/:leetcode/hash/:leetcode/heap/:leetcode/graph:leetcode/string_match:leetcode/greedy:leetcode/dp:network