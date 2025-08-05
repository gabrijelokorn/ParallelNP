package algo

import (
	partition "golang/partition/lib"
	"runtime"
	"sync"
	"sync/atomic"
)

func Sgl_stc(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))
	nThreads := runtime.GOMAXPROCS(0) * 2 // Use more threads for CPU-bound work

	for i := 0; i < len(arr); i++ {
		result[i] = 0

		numOfCombinations := int64(1) << (len(arr[i]) - 1)
		allNumbersMask := (int64(1) << len(arr[i])) - 1

		problemSum := partition.Partition_sum(arr[i], allNumbersMask)
		if problemSum%2 != 0 {
			continue
		}
		halfSum := problemSum / 2
		chunkSize := numOfCombinations / int64(nThreads)

		var wg sync.WaitGroup
		var found int32 // atomic flag instead of channel

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
					if atomic.LoadInt32(&found) == 1 {
						return
					}

					if partition.Partition_sum(arr[i], j) == halfSum {
						atomic.StoreInt32(&found, 1)
						return
					}
				}
			}(start, end)
		}

		wg.Wait()
		result[i] = atomic.LoadInt32(&found)
	}

	return result
}
