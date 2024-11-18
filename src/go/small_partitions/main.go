package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"encoding/json"
	"golang/lib"
)

func print(filename string, result []bool) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error creating file: ", filename, err)
		return
	}
	defer file.Close()

	encoder := json.NewEncoder(file)
	if err := encoder.Encode(result); err != nil {	
		fmt.Println("Error encoding JSON:", err)
		return
	}

	parallelNP.WritePartitionsArray()
}

func main() {
	// Define flags
	test := flag.String("t", "test", "Name of the test file")

	verbose := flag.Bool("v", false, "Verbose mode")

	outS := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	outP := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")

	// Parse flags
	flag.Parse()
	fmt.Println("params: ", *test, *verbose, *outS, *outP)
	
	data, err := ioutil.ReadFile(*test)
	if err != nil {
		fmt.Println("Error reading file: ", *test, err)
		return
	}

	// Decode into a map for initial parsing
	var tempMap map[string][]int
	if err := json.Unmarshal(data, &tempMap); err != nil {
		fmt.Println("Error decoding JSON:", err)
		return
	}

	fmt.Println("Data: ", string(data))
	fmt.Println("Map: ", tempMap)

	//make a 2d slice to store the data
	var arr [][]int
	for key, value := range tempMap {
		fmt.Println("Key: ", key, "Value: ", value)
		arr = append(arr, value)
	}
	fmt.Println("Data Slice: ", arr)
	fmt.Println("Data Slice 2: ", arr[1])

	var resultS []bool = make([]bool, len(arr))

	// Sequential
	for i, value := range arr {
		resultS[i] = Seq(value)
	}

	// Parallel
	// for i, value := range arr {
	// 	resultP[i] = Par(value)
	// }

	// Write to file
	print(*outS, resultS)
}