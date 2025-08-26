package algo

import (
	"fmt"
	"os"
)

func WriteState(fp *os.File, state []Coord) {
	for _, coord := range state {
		fmt.Fprintf(fp, "%f,%f\n", coord.X, coord.Y)
	}
	fmt.Fprintln(fp) // Print a newline
}
