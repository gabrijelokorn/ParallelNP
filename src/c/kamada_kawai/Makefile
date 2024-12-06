.PHONY: all clean compile measure result
all: compile run

TARGET = main.out
SOURCES = main.c ./seq.c ./par.c\
../common/file.c ../common/read.c ../common/error.c\
./json2kamada_kawai.c ./kamada_kawai2csv.c
OUTPUTS = *.csv # Later add csvs to clean, when they will be automatic

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library
CFLAGS += -fopenmp # -fopenmp is needed for OpenMP library

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "  |- $(WD)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "  |- $(WD)"
	
	@for case in $(TESTD)/$(WD)/$(TESTF); do \
		sequential=s$$(basename $$case .json).csv; \
		parallel=p$$(basename $$case .json).csv; \
		./$(TARGET) -t $$case -x $$sequential -y $$parallel -v; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###