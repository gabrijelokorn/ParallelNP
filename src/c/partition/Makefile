.PHONY: all clean compile run
all: clean compile run

TARGET = main.out
OUTPUTS = **/*.json **/*.txt
SOURCES = main.c\
./json2partitions.c partitions2json.c\
../common/file.c ../common/read.c ../common/error.c ../common/write.c\
./algo/algo.c ./algo/seq.c ./algo/mlt_stc.c ./algo/mlt_dyn.c ./algo/sgl_dyn.c ./algo/sgl_stc.c ./algo/nested.c

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

CC = gcc
CFLAGS = -ljson-c 		# -ljson-c is needed for json-c library
CFLAGS += -lm 			# -lm is needed for math library
CFLAGS += -fopenmp 		# -fopenmp is needed for OpenMP library



### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@start=$$(date +%s.%N); \
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@export OMP_NESTED=TRUE; \
	start=$$(date +%s.%N); \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		./$(TARGET) -t $$case -x $$num -v; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###

