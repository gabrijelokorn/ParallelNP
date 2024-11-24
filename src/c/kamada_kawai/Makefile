.PHONY: all clean compile measure result
all: compile run

TARGET = main.out
SOURCES = main.c ../lib/read.c ../lib/write.c ../lib/types.h ./seq.c ../lib/json2kamada_kawai.c
OUTPUTS = *.csv # Later add csvs to clean, when they will be automatic

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "  |- $(WD)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		sequential=s$$(basename $$case .json).csv; \
		parallel=p$$(basename $$case .json).csv; \
		./$(TARGET) -v -t $$case -x $$sequential -y $$parallel; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###