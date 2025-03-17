package algo

import (
	"sync"
	"runtime"
	partition "golang/partition/lib"
)

func Pool(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	threads := runtime.NumCPU()
	thread_problems := len(arr) / threads

	var wg sync.WaitGroup
	for w := 0; w < threads; w++ {
		wg.Add(1)

		go func(w int) {
			defer wg.Done()

			for i := 0; i <= thread_problems; i++ {
				
				var problem int = i*threads + w
				if problem >= len(arr) {
					break
				}

				result[problem] = 0
				var combs int64 = 1 << (len(arr[problem]) - 1)
				var all int64 = (1 << len(arr[problem])) - 1

				var problem_sum int = partition.Sum(arr[problem], len(arr[problem]), all)
				if problem_sum%2 != 0 {
					continue
				}
				var half_sum int = problem_sum / 2

				for j := int64(0); j < combs; j++ {
					var sum int = partition.Sum(arr[problem], len(arr[problem]), j)
					if sum == half_sum {
						result[problem] = 1
						break
					}
				}
			}
		}(w)
	}

	wg.Wait()

	return result
}
