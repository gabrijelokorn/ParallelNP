.PHONY: all clean compile run
all: clean compile run

TARGET = main.out
OUTPUTS = **/*.txt **/*.csv
SOURCES = main.c\
./json2kamada_kawai.c ./kamada_kawai2csv.c ./kamada_kawai.c\
../common/file.c ../common/read.c ../common/error.c ../common/write.c\
./algo/algo.c ./algo/sgl_seq.c ./algo/sgl_par.c ./algo/mlt_seq.c ./algo/mlt_par.c

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

CC = gcc
CFLAGS = -ljson-c 		# -ljson-c is needed for json-c library
CFLAGS += -lm 			# -lm is needed for math library
CFLAGS += -fopenmp 		# -fopenmp is needed for OpenMP library

#KamadaKawaiThreads ?= $(if $(K),$(K),$(shell expr $(shell nproc) / 2))
KamadaKawaiThreads ?= $(if $(K),$(K),$(shell expr $(shell nproc) / 2))
export KamadaKawaiThreads



### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@start=$$(date +%s.%N); \
	$(CC) -o $(TARGET) $(SOURCES) $(CFLAGS); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###


### --- RUN --- ###
run: $(TARGET)
	@start=$$(date +%s.%N); \
	export OMP_NESTED=TRUE; \
	export OMP_NUM_THREADS=$(KamadaKawaiThreads); \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		./$(TARGET) -t $$case -x $$num; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo "          |"; \
	echo "          |-> $(WD)      $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###
