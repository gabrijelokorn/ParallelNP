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
Repetitions ?= $(if $(R),$(R),1)
Threads ?= $(if $(THREADS),$(THREADS),$(PartitionThreads))




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
	for thread in $(Threads); do \
		export GOMAXPROCS=$$thread; \
		for case in $(TESTD)/$(WD)/$(TESTF); do \
			mkdir -p $(ALGO)/$$thread; \
			num=$$(basename $$case .json); \
			./$(TARGET) -t=$$case -x=$$num -r=$(Repetitions); \
		done; \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	shopt -s globstar nullglob; \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo "          |"; \
	echo "          |-> $(WD)      $$(echo "$$end - $$start" | bc) seconds"
	find ./algo -mindepth 1 -maxdepth 1 -type d -exec rm -rf {} +
### --- ------ --- ###