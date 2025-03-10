package parallelNP

import (
	"os"
	"time"
	"fmt"
)

func WriteTime(t time.Duration, timeFile string) {
	file, err := os.Create(timeFile)
	if err != nil {
		IOError("write.go", "Error creating the file", err)
		return
	}
	defer file.Close()

	// Convert the duration to seconds
	seconds := t.Seconds()

	// Write the duration in seconds to the file
	_, err = file.WriteString(fmt.Sprintf("%.9f\n", seconds))
	if err != nil {
		IOError("write.go", "Error writing to the file", err)
	}
}