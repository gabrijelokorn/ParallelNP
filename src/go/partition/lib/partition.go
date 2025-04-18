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

func SolvePartitionSeq(problem []int) bool {
	var numOfCombinations int64 = 1 << (len(problem) - 1)
	var allNumbersMask int64 = (1 << len(problem)) - 1

	var problem_sum int = Partition_sum(problem, allNumbersMask)
	if problem_sum%2 != 0 {
		return false
	}
	var half_problem_sum int = problem_sum / 2

	for j := int64(0); j < numOfCombinations; j++ {
		var sum int = Partition_sum(problem, j)
		if sum == half_problem_sum {
			return true
		}
	}
	return false
}
