package algo

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"time"
)

func echo(result []int32, elapsed time.Duration, algo, num string, verbose bool) {
	if verbose {
		return
	}

	algoresult := parallelNP.ParseFilename(algo, num, "json")
	partition.WritePartitions(result, algoresult)

	algotime := parallelNP.ParseFilename(algo, num, "txt")
	parallelNP.WriteTime(elapsed, algotime)
}

func Algo(arr [][]int, num string, verbose bool) {
	// Sequential
	start_seq := time.Now()
	result := Seq(arr)
	end_seq := time.Since(start_seq)
	echo(result, end_seq, "seq", num, verbose)

	// Parallel
	start_par := time.Now()
	result = Par(arr)
	end_par := time.Since(start_par)
	echo(result, end_par, "par", num, verbose)
}
