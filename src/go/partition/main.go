package main

import (
	"flag"
	"io/ioutil"
	parallelNP "golang/common"
	partition "golang/partition/lib"
	large "golang/partition/l"
	small "golang/partition/s"
)

func main() {
	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	s := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	p := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")
	v := flag.Bool("v", false, "Verbose mode")
	l := flag.Bool("l", false, "Size of the array")
	flag.Parse()

	test := *t
	verbose := *v
	outS := *s
	outP := *p
	size := *l
	
	// Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json test -> map -> slice
	var arr [][]int = partition.Json2Partitions(data)

	if (size) {
		large.Large(arr, verbose, outS, outP)
	} else {
		small.Small(arr, verbose, outS, outP)
	}
}
