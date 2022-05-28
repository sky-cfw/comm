include $(COMM_BASE_PATH)/inc.v1.mk

# BIN
BIN_TEST_RAPIDJSON = test_rapidjson_bin

# OBJ
OBJ_TEST_RAPIDJSON = test_rapidjson.o

INCLUDE = -I. -I$(COMM_BASE_PATH)/utils
LIBPATH = -L. -L$(COMM_BASE_PATH)/libs
LIBS = -lrapidjson_tools -lutils

# output
OUT_PUT = $(BIN_TEST_RAPIDJSON)

all:$(OUT_PUT)

$(BIN_TEST_RAPIDJSON): $(OBJ_TEST_RAPIDJSON)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBPATH) $(LIBS)

.PHONY: clean all
clean:
	rm -f *.o $(OUT_PUT) *.out