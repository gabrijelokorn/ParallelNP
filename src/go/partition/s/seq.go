package small

import (
	"fmt"
	"runtime"
	"sync"
)

func small_sum_seq(arr []int, size int, index int64) int {
	var sum int = 0

	for i := 0; i < size; i++ {
		if index&(1<<i) != 0 {
			sum += arr[i]
		}
	}

	return sum
}

func Seq(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))

	threads := runtime.NumCPU()

	minProblems := len(arr) / threads

	var wg sync.WaitGroup
	for w := 0; w < threads; w++ {
		wg.Add(1)

		go func(w int) {
			defer wg.Done()

			for i := 0; i <= minProblems; i++ {
				var problem int = i*threads + w
				if problem >= len(arr) {
					break
				}

				fmt.Println("Problem: ", problem)
			}
		}(w)
	}

	wg.Wait()

	return result
}
