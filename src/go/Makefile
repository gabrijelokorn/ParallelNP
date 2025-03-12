.PHONY: all clean compile run
all: clean compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

compile:
	@echo -e "##########################################\n    |-> COMPILING $(WD)"
	$(MAKE) -C partition compile
	$(MAKE) -C kamada_kawai compile
	@echo -e "\n##########################################\n\n\n"

run:
	@echo -e "##########################################\n    |-> RUNNING $(WD)"
	$(MAKE) -C partition run
	$(MAKE) -C kamada_kawai run
	@echo -e "\n##########################################\n\n\n"

clean:
	@echo -e "##########################################\n    |-> CLEANING $(WD)"
	rm -rf lib/*.o
	$(MAKE) -C partition clean
	$(MAKE) -C kamada_kawai clean
	@echo -e "\n##########################################\n\n\n"

