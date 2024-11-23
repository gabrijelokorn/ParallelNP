.PHONY: all clean run

OUTPUTS = *.json



### --- RUN --- ###
run:
	@echo "run: Julia > kamada_kawai"
	
	@for case in ../../../tests/kamada_kawai/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		julia main.jl -t $$case -x $$outs -y $$outp -v true; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(OUTPUTS)
### --- ----- --- ###