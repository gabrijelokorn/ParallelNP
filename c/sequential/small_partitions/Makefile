.PHONY: all clean compile test

CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c
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
	@echo "C language with sequential program on small_partitions"
	@for case in ../../../tests/small_partitions/*.txt; do \
		time ./$(TARGET) $$case; \
	done
# --- ---- --- #

clean:
	rm -f $(TARGET) $(OBJECTS)