.PHONY: all clean compile run

TARGET = main
SOURCES = main.go 
OUTPUTS = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "compile: Go > big_partition"
	@go build -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: Go > big_partition"
	
	@for case in ../../tests/big_partition/*.json; do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -t="$$case" -x="$$outs" -y="$$outp" -v; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###