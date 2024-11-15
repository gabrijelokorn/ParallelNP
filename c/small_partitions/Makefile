.PHONY: all clean compile run
all: compile run

TARGET = main.out
SOURCES = main.c ../lib/read.c ../lib/write.c ../lib/types.h ./seq.c ../lib/json2partitions.c ../lib/set.c
OUTPUTS = *.json

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > small_partitions"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET) compile
	@echo "run: C > small_partitions"
	
	@for case in ../../tests/small_partitions/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -v -t $$case -x $$outs -y $$outp; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###