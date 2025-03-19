package partition

func SolvePartition(problem []int) bool {
	var numOfCombinations int64 = 1 << (len(problem) - 1)
	var allNumbersMask int64 = (1 << len(problem)) - 1
	
	var problem_sum int = Sum(problem, len(problem), allNumbersMask)
	if problem_sum%2 != 0 {
		return false
	}
	var half_sum int = problem_sum / 2
	
	for j := int64(0); j < numOfCombinations; j++ {
		var sum int = Sum(problem, len(problem), j)
		if sum == half_sum {
			return true
		}
	}
	return false
}