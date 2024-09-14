.PHONY: all clean compile run

CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c ../../lib/write.c
OUTPUTS = output*.csv output*.avi

all: compile run

VERBOSE ?= 1
CFLAGS = 
ifeq ($(VERBOSE),1)
	CFLAGS += -DVERBOSE
endif

# --- COMPILE --- #
compile: $(TARGET)

$(TARGET):
	@echo "compile: C > sequential > Kamada-Kawai"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
# --- ------ --- #

# --- run --- #
run: $(TARGET)
	@echo "run: C > sequential > Kamada-Kawai"
	@for case in ../../../tests/Kamada-Kawai/*.txt; do \
		outCoords=coords$$(basename $$case .txt).csv; \
		outEdges=edges$$(basename $$case .txt).csv; \
		outVideo=output$$(basename $$case .txt).avi; \
		./$(TARGET) $$case $$outCoords $$outEdges; \
		matlab -nodisplay -nosplash -nodesktop -r "addpath('../../../'); KamadaKawai('$$outCoords', '$$outEdges', '$$outVideo'); exit;" | tail -n +11; \
	done
# --- ---- --- #


clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)