package parallelNP

import (
	"fmt"
	"os"
)

func OpenFile (filename string) *os.File {
	file, err := os.Create(filename)
	if err != nil { 
		fmt.Println("Error creating file: ", filename, err)
		return nil
	}
	return file
}

func CloseFile (file *os.File) {
	if err := file.Close(); err != nil {
		fmt.Println("Error closing file: ", err)
	}
}