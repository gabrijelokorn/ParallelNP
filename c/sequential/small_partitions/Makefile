.PHONY: all clean compile run

CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c ../../lib/write.c
OUTPUTS = output*.csv

all: compile run

VERBOSE ?= 1
CFLAGS = 
ifeq ($(VERBOSE),1)
	CFLAGS += -DVERBOSE
endif

# --- COMPILE --- #
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > sequential > small_partitions"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
# --- ------ --- #

# --- run --- #
run: $(TARGET)
	@echo "run: C > sequential > small_partitions"
	@for case in ../../../tests/small_partitions/*.txt; do \
		out=output$$(basename $$case .txt).csv; \
		./$(TARGET) $$case $$out; \
	done
# --- ---- --- #


clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)