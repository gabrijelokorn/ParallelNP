package partition

func Partition_sum(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func SolvePartition(problem []int) bool {
	var numOfCombinations int64 = 1 << (len(problem) - 1)
	var allNumbersMask int64 = (1 << len(problem)) - 1
	
	var problem_sum int = Partition_sum(problem, len(problem), allNumbersMask)
	if problem_sum%2 != 0 {
		return false
	}
	var half_sum int = problem_sum / 2
	
	for j := int64(0); j < numOfCombinations; j++ {
		var sum int = Partition_sum(problem, len(problem), j)
		if sum == half_sum {
			return true
		}
	}
	return false
}