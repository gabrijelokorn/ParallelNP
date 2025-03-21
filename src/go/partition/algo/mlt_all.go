package algo

import (
	"sync"
	partition "golang/partition/lib"
)

func Mlt_all(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	wg := sync.WaitGroup{}
	for i := 0; i < len(arr); i++ {
		result[i] = 0
		
		wg.Add(1)

		go func(i int) {
			defer wg.Done()

			if partition.SolvePartition(arr[i]) {
				result[i] = 1
			}
		}(i)
	}
	wg.Wait()

	return result
}
