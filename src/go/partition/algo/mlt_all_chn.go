package algo

import (
	"sync"
	partition "golang/partition/lib"
)

func Mlt_all_chn(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))
	var partitionsChannel = make(chan partition.Task, len(arr))

	wg := sync.WaitGroup{}
	for i := 0; i < len(arr); i++ {
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
