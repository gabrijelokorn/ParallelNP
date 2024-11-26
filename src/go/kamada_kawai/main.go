package main

import (
	"fmt"
	"encoding/json"
	"flag"
	"io/ioutil"
	"os"
	parallelNP "golang/common"
)

func main() {

	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	s := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	p := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")
	v := flag.Bool("v", false, "Verbose mode")
	flag.Parse()

	test := *t
	verbose := *v
	outS := *s
	outP := *p

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
	var resultS [][]Coord = kk.Seq()

	// Parallel
	// var resultP [][]Coord = kk.Par()

	// Print the results
	if verbose {
		// open the file
		fileS, err := os.Create(outS)
		if err != nil {
			parallelNP.IOError("large.go", "Error creating the file", err)
			fmt.Println("I dont like the golang syntax nazism: ", outP)
		}
		defer fileS.Close()


		// fileP, err := os.Create(outP)
		// if err != nil {
		// 	parallelNP.IOError("large.go", "Error creating the file", err)
		// }
		// defer fileP.Close()

		WriteVertices(fileS, resultS)
	}
}
