.PHONY: all clean compile run
all: clean compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

run:
	@echo "### ### ### >>> Running $(WD) <<< ### ### ###"
	$(MAKE) -C partition run
	$(MAKE) -C kamada_kawai run
	@echo ""

clean:
	@echo "### ### ### >>> Cleaning $(WD) <<< ### ### ###"
	$(MAKE) -C partition clean
	$(MAKE) -C kamada_kawai clean
	@echo ""
