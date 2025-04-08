package algo

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"time"
)

func run_algo(arr [][]int, algoFunc func([][]int) []int32, name string, test_id string) {
	// --- EXECTUTION --- //
	start := time.Now()
	result := algoFunc(arr)
	elapsed := time.Since(start)

	// --- WRITE RESULTS TO FILE --- //
	algoresult := parallelNP.GenerateFilename(name, test_id, "json")
	partition.WritePartitions(result, algoresult)
	// --- WRITE TIME TO FILE --- //
	algotime := parallelNP.GenerateFilename(name, test_id, "txt")
	parallelNP.WriteTime(elapsed, algotime)
}

func Algo(arr [][]int, test_id string) {
	run_algo(arr, Seq, "seq", test_id)
	run_algo(arr, Mlt_dyn_chn, "mlt_dyn_chn", test_id)
	run_algo(arr, Mlt_all_chn, "mlt_all_chn", test_id)
	run_algo(arr, Mlt_all, "mlt_all", test_id)
}
