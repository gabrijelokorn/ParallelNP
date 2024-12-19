.PHONY: all clean run

OUTPUTS = *.csv *.txt

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	
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
	rm -f $(OUTPUTS)
### --- ----- --- ###