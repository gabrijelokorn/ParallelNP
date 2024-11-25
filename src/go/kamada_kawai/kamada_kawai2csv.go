package main

import (
	"fmt"
	"os"
)

func WriteVertices(file *os.File, resultS [][]Coord) {
	for i := 0; i < len(resultS); i++ {
		for j := 0; j < len(resultS[i]); j++ {
			file.WriteString(fmt.Sprintf("%f,%f\n", resultS[i][j].X, resultS[i][j].Y))
		}
		file.WriteString("\n")
	}
}