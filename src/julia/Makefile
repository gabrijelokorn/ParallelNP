.PHONY: all clean compile run
all: clean compile run

TESTD = ../../../tests
WD = $(notdir $(CURDIR))
TESTF = *.json

run:
	@echo -e "##########################################\n    |-> RUNNING $(WD)"
	$(MAKE) -C partition run
	$(MAKE) -C kamada_kawai run
	@echo -e "##########################################\n\n\n"

julia_partition:
	@echo -e "       |\n       |-> Running $(WD)"
	$(MAKE) -C partition run

julia_kamada_kawai:
	@echo -e "       |\n       |-> Running $(WD)"
	$(MAKE) -C kamada_kawai run

clean:
	@echo -e "##########################################\n    |-> CLEANING $(WD)"
	rm -rf lib/*.o
	$(MAKE) -C partition clean
	$(MAKE) -C kamada_kawai clean
	@echo -e "##########################################\n\n\n"
