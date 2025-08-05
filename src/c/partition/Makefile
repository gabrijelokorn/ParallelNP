.PHONY: all clean compile run
all: clean compile run

TARGET = main.out
OUTPUTS = **/*.json **/*.txt
SOURCES = ./main.c\
./json2partitions.c ./partitions2json.c ./partition.c\
../common/file.c ../common/read.c ../common/error.c ../common/write.c\
./algo/algo.c ./algo/seq.c ./algo/sgl_stc.c

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

CC = gcc
CFLAGS = -ljson-c 		# -ljson-c is needed for json-c library
CFLAGS += -lm 			# -lm is needed for math library
CFLAGS += -fopenmp 		# -fopenmp is needed for OpenMP library
CFLAGS += -O2
# CFLAGS += -g -fsanitize=thread

PartitionThreads ?= $(if $(P),$(P),$(shell nproc))
export PartitionThreads
Repetitions ?= $(if $(R),$(R),1)
Threads ?= $(if $(THREADS),$(THREADS),$(PartitionThreads))



### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@start=$$(date +%s.%N); \
	$(CC) -o $(TARGET) $(SOURCES) $(CFLAGS); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@start=$$(date +%s.%N); \
	export OMP_NESTED=TRUE; \
	export OMP_CANCELLATION=true; \
	for thread in $(Threads); do \
		export OMP_NUM_THREADS=$$thread; \
		for case in $(TESTD)/$(WD)/$(TESTF); do \
			mkdir -p $(ALGO)/$$thread; \
			num=$$(basename $$case .json); \
			./$(TARGET) -t $$case -x $$num -r $(Repetitions); \
		done; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	shopt -s globstar nullglob; \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
	find ./algo -mindepth 1 -maxdepth 1 -type d -exec rm -rf {} +
### --- ------ --- ###

