.PHONY: all clean compile run

all: compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

run:
	@echo "### ### ### >>> Running $(WD) <<< ### ### ###"
	$(MAKE) -C big_partition run
	$(MAKE) -C small_partitions run
	$(MAKE) -C kamada_kawai run
	@echo ""

clean:
	$(MAKE) -C big_partition clean
	$(MAKE) -C small_partitions clean
	$(MAKE) -C kamada_kawai clean
