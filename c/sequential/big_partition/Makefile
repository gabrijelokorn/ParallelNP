.PHONY: all clean compile measure result
all: compile measure result


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



### --- MEASURE --- ###
measure: $(TARGET)
	@echo "measure: C > sequential > big_partition"
	@for case in ../../../tests/big_partition/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out; \
	done
### --- --- --- ###



### --- RESULT --- ###
result: $(TARGET)
	@echo "result: C > sequential > big_partition"
	@for case in ../../../tests/big_partition/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out --verbose; \
	done
### --- ---- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ------ --- ###
