.PHONY: all clean compile run
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c ../../lib/write.c
OUTPUTS = output*.csv


VERBOSE ?= 1
CFLAGS = 
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
	@for case in ../../../tests/big_partition/*.txt; do \
		out=output$$(basename $$case .txt).csv; \
		./$(TARGET) $$case $$out; \
	done
### --- ------ --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ------ --- ###
