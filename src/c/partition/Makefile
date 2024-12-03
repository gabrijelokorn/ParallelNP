.PHONY: all clean compile run
all: compile run

TARGET = main.out
SOURCES = main.c\
./types.h\
./s/small.c\
./l/large.c ./l/seq.c ./l/par.c\
../common/file.c ../common/read.c ../common/error.c\
./json2partitions.c partitions2json.c
OUTPUTS = *.json

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library
CFLAGS += -fopenmp # -fopenmp is needed for OpenMP library

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json
LARGE = partition/l
SMALL = partition/s


### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "  |- $(WD)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"

	@for case in $(TESTD)/$(LARGE)/$(TESTF); do \
		outs=l/s$$(basename $$case .json).json; \
		outp=l/p$$(basename $$case .json).json; \
		./$(TARGET) -t $$case -x $$outs -y $$outp -v -l; \
	done

	@for case in $(TESTD)/$(SMALL)/$(TESTF); do \
		outs=s/s$$(basename $$case .json).json; \
		outp=s/p$$(basename $$case .json).json; \
		./$(TARGET) -t $$case -x $$outs -y $$outp -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) **/$(OUTPUTS)
### --- ------ --- ###
