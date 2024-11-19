package parallelNP

func SetSum(arr []int) int {
	var sum int = 0
	for i := 0; i < len(arr); i++ {
		sum += arr[i]
	}
	return sum
}
