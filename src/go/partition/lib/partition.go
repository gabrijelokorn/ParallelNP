package partition

import (
	"runtime"
	"sync"
)

func Partition_sum(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func SolvePartitionSeq(problem []int) bool {
	var numOfCombinations int64 = 1 << (len(problem) - 1)
	var allNumbersMask int64 = (1 << len(problem)) - 1

	var problem_sum int = Partition_sum(problem, len(problem), allNumbersMask)
	if problem_sum%2 != 0 {
		return false
	}
	var half_problem_sum int = problem_sum / 2

	for j := int64(0); j < numOfCombinations; j++ {
		var sum int = Partition_sum(problem, len(problem), j)
		if sum == half_problem_sum {
			return true
		}
	}
	return false
}

func SolvePartitionPar(problem []int) bool {
	numOfCombinations := int64(1) << (len(problem) - 1)
	allNumbersMask := (int64(1) << len(problem)) - 1

	problemSum := Partition_sum(problem, len(problem), allNumbersMask)
	if problemSum%2 != 0 {
		return false
	}
	halfSum := problemSum / 2

	nThreads := runtime.GOMAXPROCS(0)
	chunkSize := numOfCombinations / int64(nThreads)

	done := make(chan struct{}) // signal for all goroutines
	var wg sync.WaitGroup
	found := make(chan bool, 1) // buffer size 1 to avoid blocking

	for w := 0; w < nThreads; w++ {
		start := int64(w) * chunkSize
		end := start + chunkSize
		if w == nThreads-1 {
			end = numOfCombinations
		}

		wg.Add(1)
		go func(start, end int64) {
			defer wg.Done()
			for j := start; j < end; j++ {
				select {
				case <-done:
					return // someone found the solution, exit
				default:
					if Partition_sum(problem, len(problem), j) == halfSum {
						select {
						case found <- true:
							close(done) // signal others to stop
						default:
						}
						return
					}
				}
			}
		}(start, end)
	}

	wg.Wait()
	select {
	case <-found:
		return true
	default:
		return false
	}
}
