package parallelNP

import (
	"runtime"
	"strconv"
)

func GenerateFilename(algo string, num string, ext string) string {
	nThreads := runtime.GOMAXPROCS(0)
	return "algo/" + strconv.Itoa(nThreads) + "/" + algo + num + "." + ext
}	
