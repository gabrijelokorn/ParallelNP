package algo

import (
	"fmt"
	partition "golang/partition/lib"
)

func Sgl_all_chn(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))
	fmt.Println("%%%---")

	for i := 0; i < len(arr); i++ {
		result[i] = 0

		fmt.Printf("Partition %d: \n", i)
		if partition.SolvePartitionPar(arr[i]) {
			result[i] = 1
		}
	}

	return result
}
