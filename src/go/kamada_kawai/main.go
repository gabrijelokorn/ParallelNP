package main

import (
	"encoding/json"
	"flag"
	"fmt"
	parallelNP "golang/lib"
	"io/ioutil"
	"os"
)

const (
	NAME = "Go > big_partition"
)

const (
	FREQUNCY = 3
)

func WriteStates(filename string, states [][]Coord) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error creating file: ", filename, err)
		return
	}
	defer file.Close()

	// write to csv file
	for i := 0; i < len(states); i++ {
		for j := 0; j < len(states[i]); j++ {
			file.WriteString(fmt.Sprintf("%f,%f\n", states[i][j].X, states[i][j].Y))
		}
		file.WriteString("\n")
	}
}

func main() {

	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	v := flag.Bool("v", false, "Verbose mode")
	s := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	p := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")
	flag.Parse()

	test := *t
	verbose := *v
	outS := *s
	outP := *p
	fmt.Println("Go > big_partition", outS)
	fmt.Println("Go > big_partition", outP)

	// 1) Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.Panic(NAME, "Error reading file: ", err)
	}

	// 2) json -> KamadaKawai struct
	var kk KamadaKawai
	err = json.Unmarshal(data, &kk)
	if err != nil {
		parallelNP.Panic(NAME, "Error unmarshalling JSON: ", err)
	}
	kk.Init()

	// Sequential
	var states [][]Coord = kk.Seq()

	// Parallel
	// for i, value := range arr {
	// 	resultP[i] = Par(value)
	// }

	// 3) Print the results
	if verbose {
		WriteStates(outS, states)
	}
}
