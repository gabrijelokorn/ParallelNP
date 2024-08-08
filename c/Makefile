.PHONY: all clean compile test

all: compile test

compile:
	$(MAKE) -C sequential/big_partition compile
#	$(MAKE) -C sequential/small_partitions compile
#	$(MAKE) -C sequential/fructerman_reingold compile
#	$(MAKE) -C parallel/big_partition compile
#	$(MAKE) -C parallel/small_partitions compile
#	$(MAKE) -C parallel/fructerman_reingold compile

test:
	$(MAKE) -C sequential/big_partition test
#	$(MAKE) -C sequential/small_partitions test
#	$(MAKE) -C sequential/fructerman_reingold test
#	$(MAKE) -C parallel/big_partition test
#	$(MAKE) -C parallel/small_partitions test
#	$(MAKE) -C parallel/fructerman_reingold test

clean:
	$(MAKE) -C sequential/big_partition clean
#	$(MAKE) -C sequential/small_partitions clean
#	$(MAKE) -C sequential/fructerman_reingold clean
#	$(MAKE) -C parallel/big_partition clean
#	$(MAKE) -C parallel/small_partitions clean
#	$(MAKE) -C parallel/fructerman_reingold clean