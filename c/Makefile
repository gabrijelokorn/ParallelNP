.PHONY: all clean compile run

all: compile run 

# Default value for VERBOSE is empty
VERBOSE ?= 1

compile:
	$(MAKE) -C sequential/big_partition compile VERBOSE=$(VERBOSE)
	$(MAKE) -C sequential/small_partitions compile VERBOSE=$(VERBOSE)
	$(MAKE) -C sequential/Kamada-Kawai compile VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/big_partition compile VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/small_partitions compile VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/Kamada-Kawai compile VERBOSE=$(VERBOSE)

run:
	$(MAKE) -C sequential/big_partition run VERBOSE=$(VERBOSE)
	$(MAKE) -C sequential/small_partitions run VERBOSE=$(VERBOSE)
	$(MAKE) -C sequential/Kamada-Kawai run VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/big_partition run VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/small_partitions run VERBOSE=$(VERBOSE)
#	$(MAKE) -C parallel/Kamada-Kawai run VERBOSE=$(VERBOSE)

clean:
	$(MAKE) -C sequential/big_partition clean
	$(MAKE) -C sequential/small_partitions clean
	$(MAKE) -C sequential/Kamada-Kawai clean
#	$(MAKE) -C parallel/big_partition clean
#	$(MAKE) -C parallel/small_partitions clean
#	$(MAKE) -C parallel/Kamada-Kawai clean