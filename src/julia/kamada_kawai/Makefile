.PHONY: all clean run

OUTPUTS = *.csv

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).csv; \
		outp=p$$(basename $$case .json).csv; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###