// package algo

// import (
// 	partition "golang/partition/lib"
// 	"runtime"
// 	"sync"
// )

// func Sgl_dyn(arr [][]int) []int32 {
// 	var result []int32 = make([]int32, len(arr))
// 	nThreads := runtime.GOMAXPROCS(0)
	
// 	for i := 0; i < len(arr); i++ {
// 		result[i] = 0

// 		numOfCombinations := int64(1) << (len(arr[i]) - 1)
// 		allNumbersMask := (int64(1) << len(arr[i])) - 1
		
// 		problemSum := partition.Partition_sum(arr[i], allNumbersMask)
// 		if problemSum%2 != 0 {
// 			continue
// 		}
// 		halfSum := problemSum / 2
// 		chunkSize := numOfCombinations / int64(nThreads)

// 		done := make(chan struct{}) // signal for all goroutines
// 		var wg sync.WaitGroup
// 		found := make(chan bool, 1) // buffer size 1 to avoid blocking

// 		for w := 0; w < nThreads; w++ {
// 			start := int64(w) * chunkSize
// 			end := start + chunkSize
// 			if w == nThreads-1 {
// 				end = numOfCombinations
// 			}

// 			wg.Add(1)
// 			go func(start, end int64) {
// 				defer wg.Done()
// 				for j := start; j < end; j++ {
// 					select {
// 					case <-done:
// 						return // someone found the solution, exit
// 					default:
// 						if partition.Partition_sum(arr[i], j) == halfSum {
// 							select {
// 							case found <- true:
// 								close(done) // signal others to stop
// 							default:
// 							}
// 							return
// 						}
// 					}
// 				}
// 			}(start, end)
// 		}

// 		wg.Wait()
// 		select {
// 		case <-found:
// 			result[i] = 1
// 		default:
// 			result[i] = 0
// 		}
// 	}

// 	return result
// }

// package algo

// import (
// 	partition "golang/partition/lib"
// 	"runtime"
// 	"sync"
// 	"sync/atomic"
// )

// func Sgl_dyna(arr [][]int) []int32 {
// 	var result []int32 = make([]int32, len(arr))
// 	nThreads := runtime.GOMAXPROCS(0)
	
// 	for i := 0; i < len(arr); i++ {
// 		result[i] = 0

// 		numOfCombinations := int64(1) << (len(arr[i]) - 1)
// 		allNumbersMask := (int64(1) << len(arr[i])) - 1
		
// 		problemSum := partition.Partition_sum(arr[i], allNumbersMask)
// 		if problemSum%2 != 0 {
// 			continue
// 		}
// 		halfSum := problemSum / 2
// 		chunkSize := numOfCombinations / int64(nThreads)

// 		var found int32 = 0  // 0 = not found, 1 = found
// 		var wg sync.WaitGroup

// 		for w := 0; w < nThreads; w++ {
// 			start := int64(w) * chunkSize
// 			end := start + chunkSize
// 			if w == nThreads-1 {
// 				end = numOfCombinations
// 			}

// 			wg.Add(1)
// 			go func(start, end int64) {
// 				defer wg.Done()
// 				for j := start; j < end; j++ {
// 					// Check if another goroutine already found the solution
// 					if atomic.LoadInt32(&found) != 0 {
// 						return
// 					}
					
// 					if partition.Partition_sum(arr[i], j) == halfSum {
// 						atomic.StoreInt32(&found, 1)
// 						return
// 					}
// 				}
// 			}(start, end)
// 		}

// 		wg.Wait()
// 		if atomic.LoadInt32(&found) != 0 {
// 			result[i] = 1
// 		}
// 	}

// 	return result
// }

// // Alternative version with less frequent atomic checks for better performance
// func Sgl_dyn(arr [][]int) []int32 {
// 	var result []int32 = make([]int32, len(arr))
// 	nThreads := runtime.GOMAXPROCS(0)
	
// 	for i := 0; i < len(arr); i++ {
// 		result[i] = 0

// 		numOfCombinations := int64(1) << (len(arr[i]) - 1)
// 		allNumbersMask := (int64(1) << len(arr[i])) - 1
		
// 		problemSum := partition.Partition_sum(arr[i], allNumbersMask)
// 		if problemSum%2 != 0 {
// 			continue
// 		}
// 		halfSum := problemSum / 2
// 		chunkSize := numOfCombinations / int64(nThreads)

// 		var found int32 = 0
// 		var wg sync.WaitGroup

// 		for w := 0; w < nThreads; w++ {
// 			start := int64(w) * chunkSize
// 			end := start + chunkSize
// 			if w == nThreads-1 {
// 				end = numOfCombinations
// 			}

// 			wg.Add(1)
// 			go func(start, end int64) {
// 				defer wg.Done()
				
// 				// Process in blocks to reduce atomic check frequency
// 				const blockSize = 1000
// 				for blockStart := start; blockStart < end; blockStart += blockSize {
// 					// Check early termination less frequently
// 					if atomic.LoadInt32(&found) != 0 {
// 						return
// 					}
					
// 					blockEnd := blockStart + blockSize
// 					if blockEnd > end {
// 						blockEnd = end
// 					}
					
// 					for j := blockStart; j < blockEnd; j++ {
// 						if partition.Partition_sum(arr[i], j) == halfSum {
// 							atomic.StoreInt32(&found, 1)
// 							return
// 						}
// 					}
// 				}
// 			}(start, end)
// 		}

// 		wg.Wait()
// 		if atomic.LoadInt32(&found) != 0 {
// 			result[i] = 1
// 		}
// 	}

// 	return result
// }

package algo

import (
	partition "golang/partition/lib"
	"runtime"
	"sync"
	"sync/atomic"
)

func Sgl_dyn(arr [][]int) []int32 {
	var result []int32 = make([]int32, len(arr))
	
	for i := 0; i < len(arr); i++ {
		result[i] = 0

		var numOfCombinations int64 = 1 << (len(arr[i]) - 1)
		var allNumbersMask int64 = (1 << len(arr[i])) - 1

		var problem_sum int = partition.Partition_sum(arr[i], allNumbersMask)
		if problem_sum%2 != 0 {
			continue
		}
		var half_problem_sum int = problem_sum / 2

		if checkPartitionBalanced(arr[i], numOfCombinations, half_problem_sum) {
			result[i] = 1
		}
	}

	return result
}

func checkPartitionBalanced(array []int, numOfCombinations int64, target int) bool {
	numWorkers := runtime.GOMAXPROCS(0)
	chunkSize := numOfCombinations / int64(numWorkers)

	// Use atomic for early termination (faster than channels)
	var found int32
	var wg sync.WaitGroup

	for w := 0; w < numWorkers; w++ {
		wg.Add(1)
		
		start := int64(w) * chunkSize
		end := start + chunkSize
		if w == numWorkers-1 {
			end = numOfCombinations
		}

		go func(start, end int64) {
			defer wg.Done()
			
			// Pin thread for better cache locality
			runtime.LockOSThread()
			defer runtime.UnlockOSThread()
			
			// Local copy to avoid false sharing
			localArray := make([]int, len(array))
			copy(localArray, array)
			arrayLen := len(localArray)
			
			// Large blocks to reduce atomic checks
			const blockSize = 32768
			
			for blockStart := start; blockStart < end; blockStart += blockSize {
				// Check early termination less frequently
				if atomic.LoadInt32(&found) != 0 {
					return
				}
				
				blockEnd := blockStart + blockSize
				if blockEnd > end {
					blockEnd = end
				}
				
				// Simple, fast inner loop
				for j := blockStart; j < blockEnd; j++ {
					sum := 0
					mask := j
					
					// Optimized but not overcomplicated
					for i := 0; i < arrayLen && mask != 0; i++ {
						if mask&1 != 0 {
							sum += localArray[i]
						}
						mask >>= 1
					}
					
					if sum == target {
						atomic.StoreInt32(&found, 1)
						return
					}
				}
			}
		}(start, end)
	}

	wg.Wait()
	return atomic.LoadInt32(&found) != 0
}