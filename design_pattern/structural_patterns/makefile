SUB_DIRS = adapter_pattern

all:
	@for sub_dir in $(SUB_DIRS);\
	do\
		echo "deal " $$sub_dir "...";\
		cd $$sub_dir && make clean && make && cd ..;\
	done

clean:
	@for sub_dir in $(SUB_DIRS);\
	do\
		echo "Cleaning " $$sub_dir "...";\
		cd $$sub_dir && make clean && cd ..;\
	done

.PHONY: clean all