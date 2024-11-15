.PHONY: all clean compile measure result
all: compile run

TARGET = main.out
SOURCES = main.c ../lib/read.c ../lib/write.c ../lib/types.h ./seq.c ../lib/json2kamada_kawai.c
OUTPUTS = *.csv # Later add csvs to clean, when they will be automatic

CC = gcc
CFLAGS = -ljson-c # -ljson-c is needed for json-c library
CFLAGS += -lm # -lm is needed for math library

### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > Kamada_Kawai"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: C > Kamada_Kawai"
	
	@for case in ../../../tests/kamada_kawai/*.json; do \
		sequential=s$$(basename $$case .json).csv; \
		parallel=p$$(basename $$case .json).csv; \
		./$(TARGET) -v -t $$case -x $$sequential -y $$parallel; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###