.PHONY: all clean compile test

CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c ../../lib/write.c
OUTPUTS = output*.csv
OBJECTS = $(SOURCES:.c=.o)

all: compile test


# --- COMPILE --- #
compile: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) -c $< -o $@
# --- ------ --- #


# --- TEST --- #
test: $(TARGET)
	@for case in ../../../tests/big_partition/*.txt; do \
		out=output$$(basename $$case .txt).csv; \
		./$(TARGET) $$case $$out; \
	done
# --- ---- --- #


clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)