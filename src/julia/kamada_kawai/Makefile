.PHONY: all clean run

OUTPUTS = *.csv



### --- RUN --- ###
run:
	@echo "run: Julia > kamada_kawai"
	
	@for case in ../../../tests/kamada_kawai/*.json; do \
		outs=s$$(basename $$case .json).csv; \
		outp=p$$(basename $$case .json).csv; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###