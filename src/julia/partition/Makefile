.PHONY: all clean run
all: clean run

OUTPUTS = **/*.json **/*.txt

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

PartitionThreads ?= $(if $(P),$(P),$(shell nproc))
export PartitionThreads
KamadaKawaiThreads ?= $(if $(K),$(K),$(shell expr $(shell nproc) / 2))
export KamadaKawaiThreads

### --- RUN --- ###
run:
	@start=$$(date +%s.%N); \
	export JULIA_NUM_THREADS=$(PartitionThreads); \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		julia main.jl -t $$case -x $$num -v true; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo "          |"; \
	echo "          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###