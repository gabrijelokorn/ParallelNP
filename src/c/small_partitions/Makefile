.PHONY: all clean compile run
all: compile run

TARGET = main.out
SOURCES = main.c ./seq.c\
../common/types.h\
../common/file.c ../common/read.c ../common/write.c ../common/error.c\
../common/json2partitions.c 
OUTPUTS = *.json

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
run: $(TARGET) compile
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -v -t $$case -x $$outs -y $$outp; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###