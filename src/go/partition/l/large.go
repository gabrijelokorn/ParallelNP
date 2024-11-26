package large

import (
	"os"
	partition "golang/partition/lib"
	parallelNP "golang/common"
)

func Large (arr [][]int, verbose bool, outS string, outP string) {
	// Sequential
	resultS := make([]bool, 1)
	resultS[0] = Seq(arr[0])

	// Write the result to the file
	if verbose {
		fileS, err := os.Create(outS)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer fileS.Close()

		partition.WritePartitions(fileS, resultS)
	}
}