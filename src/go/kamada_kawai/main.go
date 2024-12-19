package main

import (
	"encoding/json"
	"flag"
	parallelNP "golang/common"
	"io/ioutil"
	"os"
	"time"
)

func main() {

	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	s := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	p := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")
	m := flag.String("m", "unknown_seq_time_file", "File to store the length of the sequential program")
	n := flag.String("n", "unknown_par_time_file", "File to store the length of the parallel program")
	v := flag.Bool("v", false, "Verbose mode")
	flag.Parse()

	test := *t
	verbose := *v
	outS := *s
	outP := *p
	outST := *m
	outPT := *n

	// Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json -> KamadaKawai struct
	var kk KamadaKawai
	err = json.Unmarshal(data, &kk)
	if err != nil {
		parallelNP.UnmarshalError("main.go", "Error unmarshalling the JSON", err)
	}
	kk.Init()

	// Sequential
	start_seq := time.Now()
	var resultS [][]Coord = kk.Seq()
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
