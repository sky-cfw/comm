SUB_DIRS = file_io 

all:
	@for sub_dir in $(SUB_DIRS);\
	do\
		work_dir = `pwd`\
		echo "current work dir $work_dir"\
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
