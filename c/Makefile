.PHONY: all clean compile measure

all: compile measure result

compile:
	$(MAKE) -C sequential/big_partition compile
	$(MAKE) -C sequential/small_partitions compile
	$(MAKE) -C sequential/Kamada_Kawai compile
#	$(MAKE) -C parallel/big_partition compile
#	$(MAKE) -C parallel/small_partitions compile
#	$(MAKE) -C parallel/Kamada_Kawai compile

measure:
	$(MAKE) -C sequential/big_partition measure
	$(MAKE) -C sequential/small_partitions measure
	$(MAKE) -C sequential/Kamada_Kawai measure
#	$(MAKE) -C parallel/big_partition measure
#	$(MAKE) -C parallel/small_partitions measure
#	$(MAKE) -C parallel/Kamada_Kawai measure

result:
	$(MAKE) -C sequential/big_partition result
	$(MAKE) -C sequential/small_partitions result
	$(MAKE) -C sequential/Kamada_Kawai result
#	$(MAKE) -C parallel/big_partition result
#	$(MAKE) -C parallel/small_partitions result
#	$(MAKE) -C parallel/Kamada_Kawai result

clean:
	$(MAKE) -C sequential/big_partition clean
	$(MAKE) -C sequential/small_partitions clean
	$(MAKE) -C sequential/Kamada_Kawai clean
#	$(MAKE) -C parallel/big_partition clean
#	$(MAKE) -C parallel/small_partitions clean
#	$(MAKE) -C parallel/Kamada_Kawai clean