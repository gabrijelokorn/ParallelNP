.PHONY: all clean compile run

TARGET = main
SOURCES = main.go
OUTPUTS = **/*.json

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
	
	@echo large
	@for case in $(TESTD)/$(LARGE)/$(TESTF); do \
		outs=l/s$$(basename $$case .json).json; \
		outp=l/p$$(basename $$case .json).json; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -v -l; \
	done
	
# @echo small
# @for case in $(TESTD)/$(SMALL)/$(TESTF); do \
# 	outs=s/s$$(basename $$case .json).json; \
# 	outp=s/p$$(basename $$case .json).json; \
# 	./$(TARGET) -t=$$case -x=$$outs -y=$$outp -v; \
# done

### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###