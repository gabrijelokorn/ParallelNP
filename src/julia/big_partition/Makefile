.PHONY: all clean run

OUTPUTS = *.json

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- RUN --- ###
run:
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###