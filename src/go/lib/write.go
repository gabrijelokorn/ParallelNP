package parallelNP

import (
	"encoding/json"
	"fmt"
	"os"
)

func WritePartitionsArray(filename string, result []bool) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error creating file: ", filename, err)
		return
	}
	defer file.Close()

	encoder := json.NewEncoder(file)
	if err := encoder.Encode(result); err != nil {
		fmt.Println("Error encoding JSON:", err)
		return
	}
}
