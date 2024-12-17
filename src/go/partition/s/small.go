package small

import (
	"fmt"
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"os"
	"time"
)

func Small(arr [][]int, verbose bool, outS string, outP string) {
	// Sequential
	start_seq := time.Now()
	resultS := make([]int32, len(arr))
	resultS = Seq(arr)
	end_seq := time.Since(start_seq)

	// Write the result to the file
	if verbose {
		fileS, err := os.Create(outS)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer fileS.Close()

		partition.WritePartitions(fileS, resultS)

		fmt.Printf("Seq: %v\n", end_seq)
	}
}
