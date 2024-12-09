.PHONY: all clean compile run

all: compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

compile:
	@echo "### ### ### >>> Compiling $(WD) <<< ### ### ###"
	$(MAKE) -C partition compile
# $(MAKE) -C kamada_kawai compile
	@echo ""

run:
	@echo "### ### ### >>> Running $(WD) <<< ### ### ###"
	$(MAKE) -C partition run
# $(MAKE) -C kamada_kawai run
	@echo ""

clean:
	$(MAKE) -C partition clean
# $(MAKE) -C kamada_kawai clean
