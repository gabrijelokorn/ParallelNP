.PHONY: all clean big_partition small_partitions Kamada-Kawai

all: big_partition small_partitions Kamada-Kawai

big_partition:
	$(MAKE) -C big_partition

small_partitions:
	$(MAKE) -C small_partitions

Kamada-Kawai:	
	$(MAKE) -C Kamada-Kawai

clean:
	$(MAKE) -C big_partition clean
	$(MAKE) -C small_partitions clean
	$(MAKE) -C Kamada-Kawai clean