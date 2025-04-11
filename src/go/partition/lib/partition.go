package partition

import (
	"context"
	"fmt"
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
	numOfCombinations := int64(1 << (len(problem) - 1))
	allNumbersMask := int64((1 << len(problem)) - 1)

	problemSum := Partition_sum(problem, len(problem), allNumbersMask)
	if problemSum%2 != 0 {
		return false
	}
	halfProblemSum := problemSum / 2

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	found := make(chan bool, 1) // Buffered channel to prevent blocking
	var wg sync.WaitGroup

	// Limit the number of workers to the number of CPU cores
	numWorkers := runtime.NumCPU()
	work := make(chan int64, numWorkers)

	// Worker function
	worker := func() {
		defer wg.Done()
		for mask := range work {
			if Partition_sum(problem, len(problem), mask) == halfProblemSum {
				select {
				case found <- true:
					fmt.Println("found")
					cancel() // Stop other workers
				default:
				}
			}
		}
	}

	// Start worker goroutines
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go worker()
	}

	// Send tasks to workers
	go func() {
		for j := int64(0); j < numOfCombinations; j++ {
			select {
			case <-ctx.Done():
				fmt.Println("cancel")
				close(work)
				return
			default:
				work <- j
			}
		}
	}()

	// Wait for workers to finish
	go func() {
		wg.Wait()
		close(found)
	}()

	return <-found
}
