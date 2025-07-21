package main

import (
	"flag"
	parallelNP "golang/common"
	partition "golang/partition/lib"
	algo "golang/partition/algo"
	"io/ioutil"
	// "github.com/pkg/profile"
)

func main() {
	// defer profile.Start(profile.BlockProfile, profile.ProfilePath(".")).Stop()

	t := flag.String("t", "test", "Name of the test file")
	x := flag.String("x", "unknonw_testcase", "Test case id")
	r := flag.Int("r", 1, "Number of repetitions for each testcase")
	flag.Parse()

	test_path := *t
	test_id := *x
	repetitions := *r

	// Read the file
	data, err := ioutil.ReadFile(test_path)
	if err != nil {
		parallelNP.IOError("main.go", "Error reading the file", err)
	}

	// json test -> map -> slice
	var arr [][]int = partition.Json2Partitions(data)

	algo.Algo(arr, test_id, repetitions)
}
