.PHONY: all clean compile run

TARGET = main
SOURCES = main.go seq.go kamada_kawai.go
OUTPUTS = *.csv

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "compile: Go > kamada_kawai"
	@go build -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: Go > kamada_kawai"
	
	@for case in ../../../tests/kamada_kawai/*.json; do \
		outs=s$$(basename $$case .json).csv; \
		outp=p$$(basename $$case .json).csv; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -v; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###