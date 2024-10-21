.PHONY: all clean compile run
all: compile run


CC = gcc
TARGET = main.out
SOURCES = main.c
OUTPUTS = output*.csv output*.avi # Later add csvs to clean, when they will be automatic


CFLAGS = 
VERBOSE ?= 1
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
	@for case in ../../../tests/Kamada-Kawai/*.coords.txt; do \
		coords_input=$$case.coords.txt; \
		edges_input=$$case.edges.txt; \
		outPoints=points$$(basename $$case .txt).csv; \
		outCoords=coords$$(basename $$case .txt).csv; \
		outEdges=edges$$(basename $$case .txt).csv; \
		./$(TARGET) $$coords_input $$edges_input $$outPoints $$outCoords $$outEdges; \
	done
### --- --- --- ###



### --- CLEAN --- ###
clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)
### --- ----- --- ###