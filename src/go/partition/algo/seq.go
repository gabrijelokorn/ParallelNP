package algo

import (
	partition "golang/partition/lib"
)

func Seq(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	for i := 0; i < len(arr); i++ {
		result[i] = 0
		
		var combs int64 = 1 << (len(arr[i]) - 1)
		var all int64 = (1 << len(arr[i])) - 1

		var problem_sum int = partition.Sum(arr[i], len(arr[i]), all)
		if problem_sum%2 != 0 {
			continue
		}
		var half_sum int = problem_sum / 2

		for j := int64(0); j < combs; j++ {
			var sum int = partition.Sum(arr[i], len(arr[i]), j)
			if sum == half_sum {
				result[i] = 1
				break
			}
		}
	}

	return result
}
