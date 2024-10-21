.PHONY: all clean compile run
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/set.c ../../lib/write.c ../../lib/fileSize.c ../../lib/json2array.c ../../lib/types.h ../../lib/writeJson.c
OUTPUTS = output*.csv


VERBOSE ?= 1
CFLAGS = -ljson-c
ifeq ($(VERBOSE),1)
	CFLAGS += -DVERBOSE
endif



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
### --- ------ --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ------ --- ###
