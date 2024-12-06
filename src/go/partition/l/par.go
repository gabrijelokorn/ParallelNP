package large

import (
	"sync"
	"sync/atomic"
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
	var found int32 = 0
	var wg sync.WaitGroup

	// Number of workers (goroutines)
	numWorkers := 4
	chunkSize := possibilities / int64(numWorkers)
	if chunkSize == 0 {
		chunkSize = 1
	}

	// Parallelize the computation
	for w := 0; w < numWorkers; w++ {
		wg.Add(1)
		go func(start, end int64) {
			defer wg.Done()

			for i := start; i < end; i++ {
				if atomic.LoadInt32(&found) == 1 {
					return
				}

				var sum int = set_sum_seq(arr, i)
				if sum == half_sum {
					atomic.StoreInt32(&found, 1)
					return
				}
			}
		}(int64(w)*chunkSize, int64(w+1)*chunkSize)
	}

	// Wait for all goroutines to complete
	wg.Wait()

	return atomic.LoadInt32(&found) == 1
}
