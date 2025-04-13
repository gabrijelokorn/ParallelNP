package algo

import (
	parallelNP "golang/common"
	"os"
	"time"
)

func output_algo(kk *KamadaKawai, original []Coord, elapsed time.Duration, name string, test_id string) {
	// --- WRITE RESULTS TO FILE --- //
	algoresult := parallelNP.GenerateFilename(name, test_id, "csv")
	algoresult_fp, err := os.Create(algoresult)
	if err != nil {
		panic(err)
	}
	WriteState(algoresult_fp, original)
	WriteState(algoresult_fp, kk.Coords)
	defer algoresult_fp.Close()
	if err != nil {
		parallelNP.IOError("main.go", "Error closing the file", err)
	}

	// --- WRITE TIME TO FILE --- //
	algotime := parallelNP.GenerateFilename(name, test_id, "txt")
	algotime_fp, err := os.Create(algotime)
	if err != nil {
		parallelNP.IOError("main.go", "Error creating the file", err)
		return
	}
	defer algotime_fp.Close()
	parallelNP.WriteTime(algotime_fp, elapsed)
}

func run_algo(kk *KamadaKawai, algoFunc func(), name string, test_id string) {
	// --- SETUP --- //
	original := kk.set_original_coords()

	// --- EXECUTION --- //
	start := time.Now()
	algoFunc()
	elapsed := time.Since(start)

	// --- OUTPUT --- //
	output_algo(kk, original, elapsed, name, test_id)

	// --- RESET DATA --- //
	kk.get_original_coords(original)
}

func (kk *KamadaKawai) Algo(test_id string) error {
	run_algo(kk, kk.Sgl_seq, "sgl_seq", test_id)
	run_algo(kk, kk.Sgl_par, "sgl_par", test_id)

	return nil
}
