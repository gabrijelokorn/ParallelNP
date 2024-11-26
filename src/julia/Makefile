.PHONY: all clean compile run

all: compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

run:
	@echo "### ### ### >>> Running $(WD) <<< ### ### ###"
	$(MAKE) -C partition run
	$(MAKE) -C kamada_kawai run
	@echo ""

clean:
	$(MAKE) -C partition clean
	$(MAKE) -C kamada_kawai clean
