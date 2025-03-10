.PHONY: all clean compile run
all: clean compile run

OUTPUTS = **/*.txt **/*.csv

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

export JULIA_NUM_THREADS := $(shell nproc)



### --- RUN --- ###
run:
	@echo "  |- $(WD)"

	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		julia main.jl -t $$case -x $$num -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@echo "  |- $(WD)"
	rm -f $(OUTPUTS)
### --- ----- --- ###