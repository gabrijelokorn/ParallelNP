package algo

import (
	"fmt"
	"os"
	parallelNP "golang/common"
)

func WriteVertices(resultS [][]Coord, resultFile string) {
	file, err := os.Create(resultFile)
	if err != nil {
		parallelNP.IOError("algo.go", "Error creating the file", err)
	}
	defer file.Close()
	
	for i := 0; i < len(resultS); i++ {
		for j := 0; j < len(resultS[i]); j++ {
			file.WriteString(fmt.Sprintf("%f,%f\n", resultS[i][j].X, resultS[i][j].Y))
		}
		file.WriteString("\n")
	}
}