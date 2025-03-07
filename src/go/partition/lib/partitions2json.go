package partition

import (
	"encoding/json"
	"fmt"
	"os"
)

func WritePartitions(result []int32, resultFile string) {
	file, _ := os.Create(resultFile)

	// Convert to bool array
	var resultBool []bool
	for _, v := range result {
		if v == 1 {
			resultBool = append(resultBool, true)
		} else {
			resultBool = append(resultBool, false)
		}
	}

	encoder := json.NewEncoder(file)
	if err := encoder.Encode(resultBool); err != nil {
		fmt.Println("Error encoding JSON:", err)
		return
	}
}
