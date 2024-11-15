package main

import (
	"flag"
	"fmt"
)

func main() {
	// Define flags
	test := flag.String("t", "test", "Name of the test file")

	verbose := flag.Bool("v", false, "Verbose mode")

	outS := flag.String("x", "unknonw_sequential_file", "Name of the output file for the sequential program")
	outP := flag.String("y", "unknonw_parallel_file", "Name of the output file for the parallel program")

	// Parse flags
	flag.Parse()
	fmt.Println("params: ", *test, *verbose, *outS, *outP)
}
