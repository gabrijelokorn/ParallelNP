package parallelNP

import (
	"fmt"
	"os"
	"time"
)

func WriteTime(fp *os.File, t time.Duration) {
	// Convert the duration to seconds
	seconds := t.Seconds()

	_, err := fmt.Fprintf(fp, "%.9f\n", seconds)
	if err != nil {
		IOError("write.go", "Error writing to the file", err)
	}
}
