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

func run_algo(kk *KamadaKawai, algoFunc func(), name string, test_id string, repetitions int) {
	// --- SETUP --- //
	original := kk.set_original_coords()

	// --- RUN ALGORITHM R times --- //
	var avg_time time.Duration = 0.0
	for i := 0; i < repetitions; i++ {
		// --- RESET DATA --- //
		kk.get_original_coords(original)

		// --- EXECUTION --- //
		start := time.Now()
		algoFunc()
		elapsed := time.Since(start)
		avg_time = avg_time + elapsed
	}
	avg_time = avg_time / time.Duration(repetitions)

	// --- OUTPUT --- //
	output_algo(kk, original, avg_time, name, test_id)

	// --- RESET DATA --- //
	kk.get_original_coords(original)
}

func (kk *KamadaKawai) Algo(test_id string, repetitions int) error {
	run_algo(kk, kk.Sgl_seq, "sgl_seq", test_id, repetitions)
	// run_algo(kk, kk.Sgl_par, "sgl_par", test_id, repetitions)

	return nil
}
