package algo

import (
	partition "golang/partition/lib"
	"runtime"
	"sync"
)

func Nested(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	wg := sync.WaitGroup{}
	for i := 0; i < len(arr); i++ {
		result[i] = 0

		wg.Add(1)

		go func(i int) {
			defer wg.Done()

			numOfCombinations := int64(1) << (len(arr[i]) - 1)
			allNumbersMask := (int64(1) << len(arr[i])) - 1

			problemSum := partition.Partition_sum(arr[i], allNumbersMask)
			if problemSum%2 != 0 {
				return
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
							if partition.Partition_sum(arr[i], j) == halfSum {
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
				result[i] = 1
			default:
				result[i] = 0
			}
		}(i)
	}
	wg.Wait()

	return result
}
