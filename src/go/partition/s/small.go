package small

import (
	parallelNP "golang/common"
	partition "golang/partition/lib"
	"os"
	"time"
)

func Small(arr [][]int, verbose bool, outS string, outP string, outST string, outPT string) {
	// Sequential
	start_seq := time.Now()
	resultS := Seq(arr)
	end_seq := time.Since(start_seq)

	// Parallel
	start_par := time.Now()
	resultP := Par(arr)
	end_par := time.Since(start_par)

	// Write the result to the file
	if verbose {
		fileS, err := os.Create(outS)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer fileS.Close()
		partition.WritePartitions(fileS, resultS)
		timeS, err := os.Create(outST)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer timeS.Close()
		parallelNP.WriteTime(timeS, end_seq)

		fileP, err := os.Create(outP)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer fileP.Close()
		partition.WritePartitions(fileP, resultP)
		timeP, err := os.Create(outPT)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer timeP.Close()
		parallelNP.WriteTime(timeP, end_par)
	}
}
