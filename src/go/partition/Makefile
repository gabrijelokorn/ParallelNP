.PHONY: all clean compile run

TARGET = main
SOURCES = main.go
OUTPUTS = **/*.json **/*.txt

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json
LARGE = partition/l
SMALL = partition/s

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "  |- $(WD)"
	@go build -race -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(LARGE)/$(TESTF); do \
		outs=l/s$$(basename $$case .json).json; \
		outp=l/p$$(basename $$case .json).json; \
		timeseq=l/s$$(basename $$case .json)t.txt; \
		timepar=l/p$$(basename $$case .json)t.txt; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -m $$timeseq -n $$timepar -v -l; \
	done
	
	@for case in $(TESTD)/$(SMALL)/$(TESTF); do \
		outs=s/s$$(basename $$case .json).json; \
		outp=s/p$$(basename $$case .json).json; \
		timeseq=s/s$$(basename $$case .json)t.txt; \
		timepar=s/p$$(basename $$case .json)t.txt; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -m $$timeseq -n $$timepar -v; \
	done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###