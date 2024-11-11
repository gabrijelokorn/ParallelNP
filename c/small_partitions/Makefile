.PHONY: all clean compile run
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ./seq.c ../lib/set.c ../lib/write.c ../lib/fileSize.c ../lib/json2partitions.c ../lib/types.h ../lib/writeJson.c ../lib/readFile.c
OUTPUTS = output*.json

CFLAGS = -ljson-c


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