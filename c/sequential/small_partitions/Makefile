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
	@echo "compile: C > sequential > small_partitions"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET) compile
	@echo "run: C > sequential > small_partitions"
	@for case in ../../../tests/small_partitions/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out; \
	done
### --- --- --- ###



### --- TEST --- ###
test: $(TARGET) compile
	@echo "test: C > sequential > small_partitions"
	@for case in ../../../tests/small_partitions/*.json; do \
		out=output$$(basename $$case .json).json; \
		./$(TARGET) $$case $$out --verbose; \
	done
### --- ---- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###