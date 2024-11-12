.PHONY: all clean compile measure result
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ../lib/json2coords.c ../lib/json2edges.c ../lib/write.c ../lib/writeJson.c ../lib/fileSize.c ../lib/readFile.c \
../lib/json2KamadaKawai.c ../lib/writeCSV.c ../lib/KK.c ./seq.c
OUTPUTS = output*.csv output*.avi # Later add csvs to clean, when they will be automatic

CFLAGS = -ljson-c


### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > Kamada_Kawai"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: C > Kamada_Kawai"
	@for case in ../../tests/kamada_kawai/*.json; do \
		outCoordss=s$$(basename $$case .json)s.csv; \
		outCoordsp=p$$(basename $$case .json)p.csv; \
		./$(TARGET) -v -t $$case -v -x $$sequential -y $$parallel; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###