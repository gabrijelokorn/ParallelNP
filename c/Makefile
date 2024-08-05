.PHONY: all clean sequential parallel

all: sequential parallel

sequential:
	$(MAKE) -C sequential

parallel:
	$(MAKE) -C parallel

clean:
	$(MAKE) -C sequential clean
	$(MAKE) -C parallel clean