package algo

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"os"
	"time"
)

func output_algo(result []int32, elapsed time.Duration, name string, test_id string) {
	// --- WRITE RESULTS TO FILE --- //
	algoresult := parallelNP.GenerateFilename(name, test_id, "json")
	algoresult_fp, err := os.Create(algoresult)
	if err != nil {

		parallelNP.IOError("algo.go", "Error creating the file", err)
		return
	}
	defer algoresult_fp.Close()
	partition.WritePartitions(result, algoresult)
	// --- WRITE TIME TO FILE --- //
	algotime := parallelNP.GenerateFilename(name, test_id, "txt")
	algotime_fp, err := os.Create(algotime)
	if err != nil {
		parallelNP.IOError("algo.go", "Error creating the file", err)
		return
	}
	defer algotime_fp.Close()
	parallelNP.WriteTime(algotime_fp, elapsed)
}

func run_algo(arr [][]int, algoFunc func([][]int) []int32, name string, test_id string) {
	// --- EXECTUTION --- //
	start := time.Now()
	result := algoFunc(arr)
	elapsed := time.Since(start)

	// --- OUTPUT --- //
	output_algo(result, elapsed, name, test_id)
}

func Algo(arr [][]int, test_id string) {
	run_algo(arr, Seq, "seq", test_id)
	run_algo(arr, Sgl_dyn, "sgl_dyn", test_id)
	// run_algo(arr, Nested, "nested", test_id)
	// run_algo(arr, Mlt_dyn_chn, "mlt_dyn_chn", test_id)
	// run_algo(arr, Mlt_all_chn, "mlt_all_chn", test_id)
	// run_algo(arr, Mlt_all, "mlt_all", test_id)
}
