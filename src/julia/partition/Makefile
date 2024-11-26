.PHONY: all clean run

OUTPUTS = **/*.json

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json
LARGE = partition/l
SMALL = partition/s



### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(LARGE)/$(TESTF); do \
		outs=l/s$$(basename $$case .json).json; \
		outp=l/p$$(basename $$case .json).json; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true -l true; \
	done

	@for case in $(TESTD)/$(SMALL)/$(TESTF); do \
		outs=s/s$$(basename $$case .json).json; \
		outp=s/p$$(basename $$case .json).json; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###