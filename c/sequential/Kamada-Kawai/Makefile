.PHONY: all clean compile run

CC = gcc
TARGET = main.out
SOURCES = main.c ../../lib/read.c ../../lib/array.c ../../lib/set.c ../../lib/write.c
# Later add csvs to clean, when they will be automatic
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
		inPoints=points$$(basename $$case .txt).csv; \
		inCoords=coords$$(basename $$case .txt).csv; \
		inEdges=edges$$(basename $$case .txt).csv; \
		outVideo=output$$(basename $$case .txt).avi; \
		./$(TARGET) $$case $$inPoints $$inCoords $$inEdges; \
		if [ "$(VERBOSE)" = "1" ]; then \
			matlab -nodisplay -nosplash -nodesktop -r "addpath('../../../'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
		fi; \
	done
# --- ---- --- #


clean:
	rm -f $(TARGET) $(OBJECTS) $(OUTPUTS)