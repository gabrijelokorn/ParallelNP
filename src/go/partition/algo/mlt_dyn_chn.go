package algo

import (
	"sync"
	"runtime"
	partition "golang/partition/lib"
)

func Mlt_dyn_chn(arr [][]int) []int32 {
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

				if partition.SolvePartition(task.Array) {
					result[task.Index] = 1
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
