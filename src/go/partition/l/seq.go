package large

func set_sum_seq(arr []int, index int64) int {
	var sum int = 0
	for i := 0; i < len(arr); i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Seq(arr []int) bool {
	// var possibilities int64 = 1 << (len(arr) - 1)
	// var complete_set int64 = (1 << len(arr)) - 1

	// var total_sum int = set_sum_seq(arr, complete_set)
	// if total_sum%2 != 0 {
	// 	return false
	// }
	// var half_sum = total_sum / 2

	// for i := int64(1); i < possibilities; i++ {
	// 	var sum int = set_sum_seq(arr, i)
	// 	if sum == half_sum {
	// 		return true
	// 	}
	// }

	return false
}
