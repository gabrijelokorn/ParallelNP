.PHONY: all clean compile run

TARGET = main
SOURCES = main.go seq.go
OUTPUTS = *.json

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "  |- $(WD)"
	@go build -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).json; \
		outp=p$$(basename $$case .json).json; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###