package small

import (
	"os"
	partition "golang/partition/lib"
	parallelNP "golang/common"
)

func Small (arr [][]int, verbose bool, outS string, outP string) {
	// Sequential
	resultS := make([]bool, len(arr))

	for i := 0; i < len(arr); i++ {
		resultS[i] = Seq(arr[i])
	}

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