package large

import (
	"os"
	partition "golang/partition/lib"
)

func Large (arr [][]int, verbose bool, outS *os.File, outP *os.File) {
	// Sequential
	resultS := make([]bool, 1)
	resultS[0] = Seq(arr[0])

	// Write the result to the file
	if verbose {
		partition.WritePartitions(outS, resultS)
	}
}