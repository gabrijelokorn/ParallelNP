.PHONY: all clean compile run

OUTPUTS = *.json



### --- RUN --- ###
run:
	@echo "run: Julia > big_partition"
	
	@for case in ../../../tests/big_partition/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		julia main.jl -t=$$case -x=$$outs -y=$$outp -v; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###