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
	flag.Parse()

	test_name := *t
	test_id := *x

	// Read the file
	data, err := ioutil.ReadFile(test_name)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json test -> map -> slice
	var arr [][]int = partition.Json2Partitions(data)

	algo.Algo(arr, test_id)
}
