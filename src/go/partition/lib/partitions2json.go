package partition

import (
	"os"
	"encoding/json"
	"fmt"
)

func WritePartitions(file *os.File, result []bool) {
	encoder := json.NewEncoder(file)
	if err := encoder.Encode(result); err != nil {
		fmt.Println("Error encoding JSON:", err)
		return
	}
}