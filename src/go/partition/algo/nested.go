package algo

import (
	"runtime"
	"sync/atomic"
	"sync"
	partition "golang/partition/lib"
)

func Nested(arr [][]int) []int32 {
	wg := sync.WaitGroup{}
	nThreads := runtime.GOMAXPROCS(0)
	
	var result []int32 = make([]int32, len(arr))
	var partitionsChannel = make(chan partition.Task, nThreads)

	for i := 0; i < nThreads; i++ {
		wg.Add(1)

		go func(i int) {
			defer wg.Done()

			for task := range partitionsChannel {
				waitPartition := sync.WaitGroup{}
				var partitionMutex sync.RWMutex

				result[task.Index] = 0

				var combs int64 = 1 << (len(task.Array) - 1)
				var all int64 = (1 << len(task.Array)) - 1

				var problem_sum int = partition.Sum(task.Array, len(task.Array), all)
				if problem_sum%2 != 0 {
					continue
				}
				var half_sum int = problem_sum / 2

				var found int32 = 0
				for j := int64(0); j < combs; j++ {
					waitPartition.Add(1)
					if atomic.LoadInt32(&found) == 1 {
						continue
					}

					go func (k int64) {
						defer waitPartition.Done()
						partitionMutex.Lock()
						var sum int = partition.Sum(task.Array, len(task.Array), k)
						if sum == half_sum {
							atomic.StoreInt32(&found, 1)
							result[task.Index] = 1
						}
						defer partitionMutex.Unlock()
					}(j)
				}
				waitPartition.Wait()
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
