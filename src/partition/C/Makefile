FLAGS=
DEBUG?=0

ifeq ($(DEBUG), 1)
 FLAGS += -d
endif

partition_iter_C: partition_iter.c array.c read.c set.c
	@gcc partition_iter.c read.c array.c set.c -o partition_iter.out  && ./partition_iter.out ../partition_01.txt $(FLAGS)

partition_rec_C: partition_rec.c array.c read.c set.c
	@gcc partition_rec.c read.c array.c set.c -o partition_rec.out  && ./partition_rec.out ../partition_01.txt $(FLAGS)

partition_C: partition_iter_C partition_rec_C