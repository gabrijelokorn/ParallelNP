package small

import (
	"os"
	partition "golang/partition/lib"
)

func Small (arr [][]int, verbose bool, outS *os.File, outP *os.File) {
	// Sequential
	resultS := make([]bool, len(arr))

	for i := 0; i < len(arr); i++ {
		resultS[i] = Seq(arr[i])
	}

	// Write the result to the file
	if verbose {
		partition.WritePartitions(outS, resultS)
	}
}