.PHONY: all clean compile run
all: clean compile run

TARGET = main
OUTPUTS = **/*.json **/*.txt
SOURCES = main.go

ALGO = algo
TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

PartitionThreads ?= $(if $(P),$(P),$(shell nproc))
export PartitionThreads
Repetitions ?= $(if $(R),$(R),1)



### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET): $(SOURCES)
	@start=$$(date +%s.%N); \
	go build -race -o $(TARGET) $(SOURCES); \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@start=$$(date +%s.%N); \
	export GOMAXPROCS=$$PartitionThreads; \
	for case in $(TESTD)/$(WD)/$(TESTF); do \
		mkdir -p $(ALGO)/$(PartitionThreads); \
		num=$$(basename $$case .json); \
		./$(TARGET) -t=$$case -x=$$num -r=$(Repetitions); \
	done; \
	end=$$(date +%s.%N); \
	echo -e "          |\n          |-> $(WD)            $$(echo "$$end - $$start" | bc) seconds"
### --- --- --- ###



### --- CLEAN --- ###
clean:
	@start=$$(date +%s.%N); \
	rm -f $(TARGET) $(OUTPUTS); \
	end=$$(date +%s.%N); \
	echo "          |"; \
	echo "          |-> $(WD)         $$(echo "$$end - $$start" | bc) seconds"
### --- ------ --- ###