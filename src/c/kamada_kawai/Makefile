.PHONY: all clean compile measure result
all: compile run

TARGET = main.out
OUTPUTS = **/*.json **/*.txt **/*.csv
SOURCES = main.c\
./algo/algo.c ./algo/seq.c ./algo/par.c\
../common/file.c ../common/read.c ../common/error.c ../common/write.c\
./json2kamada_kawai.c ./kamada_kawai2csv.c

CC = gcc
CFLAGS = -ljson-c 		# -ljson-c is needed for json-c library
CFLAGS += -lm 			# -lm is needed for math library
CFLAGS += -fopenmp 		# -fopenmp is needed for OpenMP library

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
		num=$$(basename $$case .json); \
		./$(TARGET) -t $$case -x $$num -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@echo "  |- $(WD)"
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###