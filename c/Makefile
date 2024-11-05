.PHONY: all clean compile run

all: compile run test

compile:
	$(MAKE) -C sequential/big_partition compile
	$(MAKE) -C sequential/small_partitions compile
	$(MAKE) -C sequential/Kamada_Kawai compile
#	$(MAKE) -C parallel/big_partition compile
#	$(MAKE) -C parallel/small_partitions compile
#	$(MAKE) -C parallel/Kamada_Kawai compile

run:
	$(MAKE) -C sequential/big_partition run
	$(MAKE) -C sequential/small_partitions run
	$(MAKE) -C sequential/Kamada_Kawai run
#	$(MAKE) -C parallel/big_partition run
#	$(MAKE) -C parallel/small_partitions run
#	$(MAKE) -C parallel/Kamada_Kawai run

test:
	$(MAKE) -C sequential/big_partition test
	$(MAKE) -C sequential/small_partitions test
	$(MAKE) -C sequential/Kamada_Kawai test
#	$(MAKE) -C parallel/big_partition test
#	$(MAKE) -C parallel/small_partitions test
#	$(MAKE) -C parallel/Kamada_Kawai test

clean:
	$(MAKE) -C sequential/big_partition clean
	$(MAKE) -C sequential/small_partitions clean
	$(MAKE) -C sequential/Kamada_Kawai clean
#	$(MAKE) -C parallel/big_partition clean
#	$(MAKE) -C parallel/small_partitions clean
#	$(MAKE) -C parallel/Kamada_Kawai clean