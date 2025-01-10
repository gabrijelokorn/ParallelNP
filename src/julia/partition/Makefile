.PHONY: all clean run

OUTPUTS = **/*.json **/*.txt

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json
LARGE = partition/l
SMALL = partition/s

export JULIA_NUM_THREADS := $(shell nproc)

### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(LARGE)/$(TESTF); do \
		outs=l/s$$(basename $$case .json).json; \
		outp=l/p$$(basename $$case .json).json; \
		timeseq=l/s$$(basename $$case .json)t.txt; \
		timepar=l/p$$(basename $$case .json)t.txt; \
		julia main.jl -t $$case -x $$outs -y $$outp -m $$timeseq -n $$timepar -v true -l true; \
	done

	@for case in $(TESTD)/$(SMALL)/$(TESTF); do \
		outs=s/s$$(basename $$case .json).json; \
		outp=s/p$$(basename $$case .json).json; \
		timeseq=s/s$$(basename $$case .json)t.txt; \
		timepar=s/p$$(basename $$case .json)t.txt; \
		julia main.jl -t $$case -x $$outs -y $$outp -m $$timeseq -n $$timepar -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###