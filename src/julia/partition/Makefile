.PHONY: all clean run
all: clean run

OUTPUTS = **/*.json **/*.txt

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

PartitionThreads ?= $(if $(P),$(P),$(shell nproc))
export PartitionThreads
Repetitions ?= $(if $(R),$(R),1)
Threads ?= $(if $(THREADS),$(THREADS),$(PartitionThreads))



### --- RUN --- ###
run:
	@start=$$(date +%s.%N); \
	for thread in $(Threads); do \
		export JULIA_NUM_THREADS=$$thread; \
		for case in $(TESTD)/$(WD)/$(TESTF); do \
			mkdir -p $(ALGO)/$$thread; \
			num=$$(basename $$case .json); \
			julia main.jl -t $$case -x $$num -r $(Repetitions); \
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
	echo "          |"; \
	echo "          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###