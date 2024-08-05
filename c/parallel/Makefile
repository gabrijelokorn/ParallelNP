.PHONY: all clean big_partition small_partitions fructerman_reingold

all: big_partition small_partitions fructerman_reingold

big_partition:
	$(MAKE) -C big_partition

small_partitions:
	$(MAKE) -C small_partitions

fructerman_reingold:	
	$(MAKE) -C fructerman_reingold

clean:
	$(MAKE) -C big_partition clean
	$(MAKE) -C small_partitions clean
	$(MAKE) -C fructerman_reingold clean