package main

import (
	"encoding/json"
	"flag"
	parallelNP "golang/common"
	algo "golang/kamada_kawai/algo"
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

	// json -> KamadaKawai struct
	var kk algo.KamadaKawai
	err = json.Unmarshal(data, &kk)
	if err != nil {
		parallelNP.UnmarshalError("main.go", "Error unmarshalling the JSON", err)
	}
	kk.Init()

	kk.Algo(num, nThreads, verbose)
}
