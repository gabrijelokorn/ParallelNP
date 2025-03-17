package main

import (
	"flag"
	parallelNP "golang/common"
	partition "golang/partition/lib"
	algo "golang/partition/algo"
	"io/ioutil"
)

func main() {
	// Define flags
	t := flag.String("t", "test", "Name of the test file")
	x := flag.String("x", "unknonw_testcase", "Test case id")
	n := flag.Int("n", 1, "Number of threads")
	v := flag.Bool("v", false, "Verbose mode")
	flag.Parse()

	test := *t
	num := *x
	nThreads := *n
	verbose := *v

	// Read the file
	data, err := ioutil.ReadFile(test)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json test -> map -> slice
	var arr [][]int = partition.Json2Partitions(data)

	algo.Algo(arr, num, nThreads, verbose)
}
