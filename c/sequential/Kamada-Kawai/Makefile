.PHONY: all clean compile run
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/json2coords.c ../../lib/json2edges.c ../../lib/write.c ../../lib/writeJson.c ../../lib/fileSize.c ../../lib/readFile.c \
../../lib/json2KamadaKawai.c
OUTPUTS = output*.csv output*.avi # Later add csvs to clean, when they will be automatic


VERBOSE ?= 1
CFLAGS = -ljson-c
ifeq ($(VERBOSE),1)
	CFLAGS += -DVERBOSE
endif


### --- COMPILE --- ###
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > sequential > Kamada-Kawai"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
### --- ------ --- ###



### --- RUN --- ###
run: $(TARGET)
	@echo "run: C > sequential > Kamada-Kawai"
	@for case in ../../../tests/Kamada-Kawai/*.json; do \
		outPoints=points$$(basename $$case .json).csv; \
		outCoords=coords$$(basename $$case .json).csv; \
		outEdges=edges$$(basename $$case .json).csv; \
		./$(TARGET) $$case $$outPoints $$outCoords $$outEdges; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###