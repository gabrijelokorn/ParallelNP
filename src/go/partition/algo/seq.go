package algo

import (
	partition "golang/partition/lib"
)

func Seq(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	for i := 0; i < len(arr); i++ {
		result[i] = 0
		
		if partition.SolvePartition(arr[i]) {
			result[i] = 1
		}
	}

	return result
}
