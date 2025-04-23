package algo

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"os"
	"time"
)

func output_algo(result []int32, avg_time time.Duration, name string, test_id string) {
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
	parallelNP.WriteTime(algotime_fp, avg_time)
}

func run_algo(arr [][]int, algoFunc func([][]int) []int32, name string, test_id string, repetitions int) {
	// --- SETUP --- //
	result := make([]int32, len(arr))
	
	// --- EXECTUTION --- //
	var avg_time time.Duration = 0.0
	for i := 0; i < repetitions; i++ {
		start := time.Now()
		result = algoFunc(arr)
		elapsed := time.Since(start)
		avg_time = avg_time + elapsed
	}
	avg_time = avg_time / time.Duration(repetitions)

	output_algo(result, avg_time, name, test_id)
}

func Algo(arr [][]int, test_id string, repetitions int) {
	run_algo(arr, Seq, "seq", test_id, repetitions)
	run_algo(arr, Sgl_dyn, "sgl_dyn", test_id, repetitions)
}
