.PHONY: all clean run

OUTPUTS = *.json



### --- RUN --- ###
run:
	@echo "run: Julia > small_partitions"
	
	@for case in ../../../tests/small_partitions/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###