package main

import (
	"encoding/json"
	"flag"
	parallelNP "golang/common"
	algo "golang/kamada_kawai/algo"
	"io/ioutil"
	"os"
	"time"
)

func main() {

	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	x := flag.String("x", "unknonw_testcase", "Test case id")
	v := flag.Bool("v", false, "Verbose mode")
	flag.Parse()

	test := *t
	num := *x
	verbose := *v

	// Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json -> KamadaKawai struct
	var kk kamada_kawai.KamadaKawai
	err = json.Unmarshal(data, &kk)
	if err != nil {
		parallelNP.UnmarshalError("main.go", "Error unmarshalling the JSON", err)
	}
	kk.Init()

	// Sequential
	start_seq := time.Now()
	var resultS [][]kamada_kawai.Coord = kk.Seq()
	end_seq := time.Since(start_seq)

	// Reassign the initial positions
	for i := 0; i < kk.N; i++ {
		kk.Coords[i].X = resultS[0][i].X
		kk.Coords[i].Y = resultS[0][i].Y
	}

	// Parallel
	start_par := time.Now()
	var resultP [][]Coord = kk.Par()
	end_par := time.Since(start_par)

	// Print the results
	if verbose {
		// open the file
		fileS, err := os.Create(outS)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer fileS.Close()
		WriteVertices(fileS, resultS)
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
		WriteVertices(fileP, resultP)
		timeP, err := os.Create(outPT)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
		}
		defer timeP.Close()
		parallelNP.WriteTime(timeP, end_par)
	}
}
