package algo

import (
	partition "golang/partition/lib"
)

func Seq(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	for i := 0; i < len(arr); i++ {
		result[i] = 0

		var numOfCombinations int64 = 1 << (len(arr[i]) - 1)
		var allNumbersMask int64 = (1 << len(arr[i])) - 1

		var problem_sum int = partition.Partition_sum(arr[i], allNumbersMask)
		if problem_sum%2 != 0 {
			continue
		}
		var half_problem_sum int = problem_sum / 2

		for j := int64(0); j < numOfCombinations; j++ {
			var sum int = partition.Partition_sum(arr[i], j)
			if sum == half_problem_sum {
				result[i] = 1
			}
		}
	}

	return result
}
