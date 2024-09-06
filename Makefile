# Compile the sequential and parallel versions 
# of the program in all languages.

.PHONY: all clean compile run c julia golang

all: compile run

# Default value for VERBOSE is empty
VERBOSE ?= 1

compile:
	$(MAKE) -C c compile VERBOSE=$(VERBOSE)
#	$(MAKE) -C golang compile VERBOSE=$(VERBOSE)
#	$(MAKE) -C julia compile VERBOSE=$(VERBOSE)

run:
	$(MAKE) -C c run VERBOSE=$(VERBOSE)
#	$(MAKE) -C golang run VERBOSE=$(VERBOSE)
#	$(MAKE) -C julia run VERBOSE=$(VERBOSE)

c:
	$(MAKE) -C c VERBOSE=$(VERBOSE)

julia:
	$(MAKE) -C julia VERBOSE=$(VERBOSE)

golang:
	$(MAKE) -C golang VERBOSE=$(VERBOSE)

clean:
	$(MAKE) -C c clean
#	$(MAKE) -C golang clean
#	$(MAKE) -C julia clean