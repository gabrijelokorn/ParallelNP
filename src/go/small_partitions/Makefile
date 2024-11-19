.PHONY: all clean compile run

TARGET = main
SOURCES = main.go seq.go 
OUTPUTS = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "compile: Go > small_partitions"
	@go build -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: Go > small_partitions"
	
	@for case in ../../../tests/small_partitions/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -v; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###