# Compile the sequential and parallel versions 
# of the program in all languages.

.PHONY: all clean c golang julia

all: build

build: c golang julia

c:
	$(MAKE) -C c

golang:
#	$(MAKE) -C golang

julia:
#	$(MAKE) -C julia

clean:
	$(MAKE) -C c clean
#	$(MAKE) -C golang clean
#	$(MAKE) -C julia clean