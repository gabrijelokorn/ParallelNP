package parallelNP

import (
	"os"
	"time"
)

func WriteTime(file *os.File, t time.Duration) {
	_, err := file.WriteString(t.String())
	if err != nil {
		IOError("write.go", "Error writing the time to the file", err)
	}
}
