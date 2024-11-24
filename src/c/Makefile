.PHONY: all clean compile run

all: compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

compile:
	@echo "### ### ### >>> Compiling $(WD) <<< ### ### ###"
	$(MAKE) -C big_partition compile
	$(MAKE) -C small_partitions compile
	$(MAKE) -C kamada_kawai compile
	@echo ""

run:
	@echo "### ### ### >>> Running $(WD) <<< ### ### ###"
	$(MAKE) -C big_partition run
	$(MAKE) -C small_partitions run
	$(MAKE) -C kamada_kawai run
	@echo ""

clean:
	rm -rf lib/*.o
	$(MAKE) -C big_partition clean
	$(MAKE) -C small_partitions clean
	$(MAKE) -C kamada_kawai clean