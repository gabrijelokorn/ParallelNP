.PHONY: all clean compile run
all: compile run test


CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/set.c ../../lib/write.c ../../lib/fileSize.c ../../lib/json2partitions.c ../../lib/types.h ../../lib/writeJson.c ../../lib/readFile.c
OUTPUTS = output*.json

CFLAGS = -ljson-c


### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > sequential > big_partition"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: C > sequential > big_partition"
	@for case in ../../../tests/big_partition/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out; \
	done
### --- --- --- ###



### --- TEST --- ###
test: $(TARGET)
	@echo "test: C > sequential > big_partition"
	@for case in ../../../tests/big_partition/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out --verbose; \
	done
### --- ---- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ------ --- ###
