package algo

import (
	parallelNP "golang/common"
	"time"
)

func rewindVertices(kk *KamadaKawai, result [][]Coord) {
	for i := 0; i < kk.N; i++ {
		kk.Coords[i].X = result[0][i].X
		kk.Coords[i].Y = result[0][i].Y
	}
}

func echo (kk *KamadaKawai, result [][]Coord, elapsed time.Duration, algo, num string, verbose bool) {
	if !verbose {
		return
	}

	algoresult := parallelNP.GenerateFilename(algo, num, "csv")
	WriteVertices(result, algoresult)

	algotime := parallelNP.GenerateFilename(algo, num, "txt")
	parallelNP.WriteTime(elapsed, algotime)
}

func (kk *KamadaKawai) Algo(num string, verbose bool) error {

	// Sequential
	start := time.Now()
	var result [][]Coord = kk.Seq()
	end := time.Since(start)
	echo(kk, result, end, "seq", num, verbose)
	rewindVertices(kk, result)

	// Parallel
	start = time.Now()
	result = kk.Par()
	end = time.Since(start)
	echo(kk, result, end, "par", num, verbose)
	rewindVertices(kk, result)

	return nil
}
	