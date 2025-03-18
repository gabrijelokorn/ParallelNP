package algo

import (
	"sync"
	"runtime"
	partition "golang/partition/lib"
)

func Mlt_dyn(arr [][]int) []int32 {
	wg := sync.WaitGroup{}
	nThreads := runtime.GOMAXPROCS(0)
	
	var result []int32 = make([]int32, len(arr))
	var partitionsChannel = make(chan partition.Task, nThreads)

	for i := 0; i < nThreads; i++ {
		wg.Add(1)

		go func(i int) {
			defer wg.Done()

			for task := range partitionsChannel {
				result[task.Index] = 0

				var combs int64 = 1 << (len(task.Array) - 1)
				var all int64 = (1 << len(task.Array)) - 1

				var problem_sum int = partition.Sum(task.Array, len(task.Array), all)
				if problem_sum%2 != 0 {
					continue
				}
				var half_sum int = problem_sum / 2

				for j := int64(0); j < combs; j++ {
					var sum int = partition.Sum(task.Array, len(task.Array), j)
					if sum == half_sum {
						result[task.Index] = 1
						break
					}
				}
			}
		}(i)
	}

	for i, problem := range arr {
		partitionsChannel <- partition.Task{Index: i, Array: problem}
	}
	close(partitionsChannel)

	wg.Wait()
	return result
}
