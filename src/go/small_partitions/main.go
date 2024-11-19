package main

import (
	"encoding/json"
	"flag"
	"fmt"
	parallelNP "golang/lib"
	"io/ioutil"
	"strconv"
)

const (
	NAME = "Go > small_partitions"
)

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
	fmt.Println("Go > small_partitions", outP)

	// 1) Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.Panic(NAME, "Error reading file: ", err)
	}

	// 2) json test -> map -> slice
	var tempMap map[string][]int
	if err := json.Unmarshal(data, &tempMap); err != nil {
		parallelNP.Panic(NAME, "Error unmarshalling JSON: ", err)
	}

	var arr = make([][]int, len(tempMap))
	for key, value := range tempMap {
		index, err := strconv.Atoi(key)
		if err != nil {
			parallelNP.Panic(NAME, "Error converting key to int: ", err)
		}
		arr[index-1] = value
	}

	var resultS []bool = make([]bool, len(arr))

	// Sequential
	for i, value := range arr {
		resultS[i] = Seq(value)
	}

	// Parallel
	// for i, value := range arr {
	// 	resultP[i] = Par(value)
	// }

	// 3) Print the results
	if verbose {
		parallelNP.WritePartitionsArray(outS, resultS)
	}
}
