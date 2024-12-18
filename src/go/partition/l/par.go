package large

import (
	"runtime"
	"sync"
	"sync/atomic"
)

func large_sum_par(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Par(arr []int) int32 {
	var result int32 = 0

	var combs int64 = 1 << (len(arr) - 1)
	var all int64 = (1 << len(arr)) - 1

	// Calculate the total sum of the array
	var problem_sum int = large_sum_par(arr, len(arr), all)
	if problem_sum%2 != 0 {
		return 0
	}
	var half_sum = problem_sum / 2

	// Shared variable to indicate if a solution is found
	// var found int32 = 0
	var wg sync.WaitGroup

	threads := runtime.NumCPU()
	minProblems := combs / int64(threads)

	// Parallelize the computation
	for w := 0; w < threads; w++ {
		wg.Add(1)

		go func(w int) {
			defer wg.Done()

			for i := 0; i <= int(minProblems); i++ {
				var index int64 = int64(i*threads + w)
				if index >= combs {
					break
				}

				if atomic.LoadInt32(&result) == 1 {
					break
				}

				if large_sum_par(arr, len(arr), index) == half_sum {
					atomic.StoreInt32(&result, 1)
				}
			}

		}(int(w))
	}

	// Wait for all goroutines to complete
	wg.Wait()

	return result
}
