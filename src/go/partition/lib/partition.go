package partition

func Partition_sum(arr []int, index int64) int {
	var sum int = 0

	for i := 0; i < len(arr); i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}
