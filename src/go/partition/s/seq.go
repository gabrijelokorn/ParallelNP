package small

import (
)

func small_sum_seq(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Seq(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	for i := 0; i < len(arr); i++ {
		result[i] = 0
		
		var combs int64 = 1 << (len(arr[i]) - 1)
		var all int64 = (1 << len(arr[i])) - 1

		var problem_sum int = small_sum_seq(arr[i], len(arr[i]), all)
		if problem_sum%2 != 0 {
			continue
		}
		var half_sum int = problem_sum / 2

		for j := int64(0); j < combs; j++ {
			var sum int = small_sum_seq(arr[i], len(arr[i]), j)
			if sum == half_sum {
				result[i] = 1
				break
			}
		}
	}

	return result
}
