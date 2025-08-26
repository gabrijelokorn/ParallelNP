package main

import (
	"encoding/json"
	"flag"
	parallelNP "golang/common"
	algo "golang/kamada_kawai/algo"
	"io/ioutil"

	"github.com/pkg/profile"
)

func main() {
	defer profile.Start(profile.CPUProfile, profile.ProfilePath(".")).Stop()

	// Define flags
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

	// json -> KamadaKawai struct
	var kk algo.KamadaKawai
	err = json.Unmarshal(data, &kk)
	if err != nil {
		parallelNP.UnmarshalError("main.go", "Error unmarshalling the JSON", err)
	}
	kk.Init()

	kk.Algo(test_id, repetitions)
}
