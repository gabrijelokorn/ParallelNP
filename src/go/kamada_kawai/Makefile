.PHONY: all clean compile run

TARGET = main
SOURCES = main.go seq.go par.go\
kamada_kawai.go kamada_kawai2csv.go
OUTPUTS = *.csv *.json *.txt

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "  |- $(WD)"
	@go build -race -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		outs=s$$(basename $$case .json).csv; \
		outp=p$$(basename $$case .json).csv; \
		timeseq=s$$(basename $$case .json)t.txt; \
		timepar=p$$(basename $$case .json)t.txt; \
		./$(TARGET) -t=$$case -x=$$outs -y=$$outp -m=$$timeseq -n=$$timepar -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###