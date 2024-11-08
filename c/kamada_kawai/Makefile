.PHONY: all clean compile measure result
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ../lib/json2coords.c ../lib/json2edges.c ../lib/write.c ../lib/writeJson.c ../lib/fileSize.c ../lib/readFile.c \
../lib/json2KamadaKawai.c ../lib/writeCSV.c ../lib/KK.c
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
	@for case in ../../tests/Kamada_Kawai/*.json; do \
		outPointss=points$$(basename $$case .json)s.csv; \
		outCoordss=coords$$(basename $$case .json)s.csv; \
		outEdgess=edges$$(basename $$case .json)s.csv; \
		outPointsp=points$$(basename $$case .json)p.csv; \
		outCoordsp=coords$$(basename $$case .json)p.csv; \
		outEdgesp=edges$$(basename $$case .json)p.csv; \
		./$(TARGET) -t $$case -x $$outPointss -y $$outCoordss -z $$outEdgess -a $$outPointsp -b $$outCoordsp -c $$outEdgesp; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###