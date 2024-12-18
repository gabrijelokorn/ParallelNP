package large

func large_sum_seq(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Seq(arr []int) int32 {
	var combs int64 = 1 << (len(arr) - 1)
	var all int64 = (1 << len(arr)) - 1

	var problem_sum int = large_sum_seq(arr, len(arr), all)
	if problem_sum%2 != 0 {
		return 0
	}
	var half_sum = problem_sum / 2

	for i := int64(1); i < combs; i++ {
		var sum int = large_sum_seq(arr, len(arr), i)
		if sum == half_sum {
			return 1
		}
	}

	return 0
}
