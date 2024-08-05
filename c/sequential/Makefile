CC = gcc
TARGET = main.out
SOURCES = main.c ../lib/read.c ../lib/array.c ../lib/set.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
