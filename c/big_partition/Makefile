.PHONY: all clean compile run
all: compile run

TARGET = main.out
SOURCES = main.c ./seq.c ../lib/set.c ../lib/write.c ../lib/fileSize.c ../lib/json2partitions.c ../lib/types.h ../lib/writeJson.c ../lib/readFile.c
OUTPUTS = *.json

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > big_partition"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: C > big_partition"
	
	@for case in ../../tests/big_partition/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -v -t $$case -x $$outs -y $$outp; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ------ --- ###
