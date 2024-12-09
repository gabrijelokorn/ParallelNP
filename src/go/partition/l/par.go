package large

import (
	"sync"
	"runtime"
	"fmt"
)

func set_sum_par(arr []int, index int64) int {
	var sum int = 0
	for i := 0; i < len(arr); i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Par(arr []int) bool {
	var possibilities int64 = 1 << (len(arr) - 1)
	var complete_set int64 = (1 << len(arr)) - 1

	// Calculate the total sum of the array
	var total_sum int = set_sum_seq(arr, complete_set)
	if total_sum%2 != 0 {
		return false
	}
	var half_sum = total_sum / 2

	// Shared variable to indicate if a solution is found
	// var found int32 = 0
	var wg sync.WaitGroup

	// Number of workers (goroutines)
	fmt.Println("Number of CPUs: ", runtime.NumCPU())
	numWorkers := runtime.NumCPU()
	chunkSize := possibilities / int64(numWorkers)
	if chunkSize == 0 {
		chunkSize = 1
	}

	// Parallelize the computation
	for w := 0; w < numWorkers; w++ {
		wg.Add(1)

		go func(w int64) {
			defer wg.Done()

			var start int64 = w * chunkSize
			var end int64 = (w + 1) * chunkSize
			if w == int64(numWorkers-1) {
				end = possibilities
			}

			fmt.Println("Worker ", w, " start: ", start, " end: ", end)
		}(int64(w))
	}

	// Wait for all goroutines to complete
	wg.Wait()

	fmt.Println("Unused variables: ", chunkSize, possibilities, half_sum)
	return true
}
