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

func run_with_timeout(kk *KamadaKawai, algoFunc(func() [][]Coord), verbose bool, name string, num string) {
	start := time.Now()
	result := algoFunc()
	elapsed := time.Since(start)
	
	rewindVertices(kk, result)
	
	if !verbose {
		return
	}
	algoresult := parallelNP.GenerateFilename(name, num, "csv")
	WriteVertices(result, algoresult)
	
	algotime := parallelNP.GenerateFilename(name, num, "txt")
	parallelNP.WriteTime(elapsed, algotime)
}

func (kk *KamadaKawai) Algo(num string, verbose bool) error {
	run_with_timeout(kk, kk.Seq, verbose, "seq", num)
	run_with_timeout(kk, kk.Par, verbose, "par", num)
	return nil 
}
	