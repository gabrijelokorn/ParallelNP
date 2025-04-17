.PHONY: all clean compile run
all: clean compile run

OUTPUTS = **/*.txt **/*.csv

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

KamadaKawaiThreads ?= $(if $(K),$(K),$(shell expr $(shell nproc) / 2))
export KamadaKawaiThreads



### --- RUN --- ###
run:
	@start=$$(date +%s.%N); \
	export JULIA_NUM_THREADS=$(KamadaKawaiThreads); \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		perf stat -e cache-misses,cache-references,LLC-load-misses,LLC-store-misses julia main.jl -t $$case -x $$num; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)      $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###