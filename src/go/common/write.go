package parallelNP

import (
	"os"
	"time"
)

func WriteTime(t time.Duration, timeFile string) {
	file, err := os.Create(timeFile)

	if err != nil {
		IOError("write.go", "Error creating the file", err)
	}

	file.WriteString(t.String())
}
