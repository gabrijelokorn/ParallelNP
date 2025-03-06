.PHONY: all clean compile run
all: clean compile run

TARGET = main
OUTPUTS = **/*.json **/*.txt
SOURCES = main.go

ALGO = algo
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
		num=$$(basename $$case .json); \
		./$(TARGET) -t=$$case -x=$$num -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@echo "  |- $(WD)"
	rm -f $(TARGET) $(OUTPUTS)
### --- ----- --- ###