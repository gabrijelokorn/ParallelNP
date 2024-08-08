# Compile the sequential and parallel versions 
# of the program in all languages.

.PHONY: all clean compile test c julia golang

all: compile test

compile:
	$(MAKE) -C c compile
#	$(MAKE) -C golang compile
#	$(MAKE) -C julia compile

test:
	$(MAKE) -C c test
#	$(MAKE) -C golang test
#	$(MAKE) -C julia test

c:
	$(MAKE) -C c

julia:
	$(MAKE) -C julia

golang:
	$(MAKE) -C golang

clean:
	$(MAKE) -C c clean
#	$(MAKE) -C golang clean
#	$(MAKE) -C julia clean