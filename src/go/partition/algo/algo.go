package algo

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"time"
)

func run_with_timeout(arr [][]int, algoFunc(func([][]int) []int32), verbose bool, name string, num string) {
	start := time.Now()
	result := algoFunc(arr)
	elapsed := time.Since(start)
	
	if !verbose {
		return
	}
	algoresult := parallelNP.GenerateFilename(name, num, "json")
	partition.WritePartitions(result, algoresult)
	
	algotime := parallelNP.GenerateFilename(name, num, "txt")
	parallelNP.WriteTime(elapsed, algotime)
}

func Algo(arr [][]int, num string, verbose bool) {
	run_with_timeout(arr, Seq, verbose, "seq", num)
	run_with_timeout(arr, Mlt_dyn_chn, verbose, "mlt_dyn_chn", num)	
	run_with_timeout(arr, Mlt_all_chn, verbose, "mlt_all_chn", num)
	run_with_timeout(arr, Mlt_all, verbose, "mlt_all", num)
}

