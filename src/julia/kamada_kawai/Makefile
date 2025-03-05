.PHONY: all clean run
all: clean run

OUTPUTS = *.csv *.txt

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

export JULIA_NUM_THREADS := $(shell nproc)



### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	@export JULIA_NUM_THREADS=$(nproc)  # For Linux

	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).csv; \
		outp=p$$(basename $$case .json).csv; \
		timeseq=s$$(basename $$case .json)t.txt; \
		timepar=p$$(basename $$case .json)t.txt; \
		julia main.jl -t $$case -x $$outs -y $$outp -m $$timeseq -n $$timepar -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@echo "  |- $(WD)"
	rm -f $(OUTPUTS)
### --- ----- --- ###