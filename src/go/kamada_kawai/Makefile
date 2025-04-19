.PHONY: all clean compile run
all: clean compile run

TARGET = main
OUTPUTS = **/*.txt **/*.csv
SOURCES = main.go

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

KamadaKawaiThreads ?= $(if $(K),$(K),$(shell expr $(shell nproc) / 2))
export KamadaKawaiThreads



### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@start=$$(date +%s.%N); \
	go build -race -o $(TARGET) $(SOURCES); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@start=$$(date +%s.%N); \
	export GOMAXPROCS=$(KamadaKawaiThreads); \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		num=$$(basename $$case .json); \
		./$(TARGET) -t=$$case -x=$$num; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo "          |"; \
	echo "          |-> $(WD)      $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###