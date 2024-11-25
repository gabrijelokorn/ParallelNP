package partition

import (
	"strconv"
	"encoding/json"
	parallelNP "golang/common"
)

func Json2Partitions(data []byte) [][]int {
	var tempMap map[string][]int
	if err := json.Unmarshal(data, &tempMap); err != nil {
		parallelNP.Panic("Json2Partitions", "Error unmarshalling JSON: ", err)
	}

	var arr = make([][]int, len(tempMap))
	for key, value := range tempMap {
		index, err := strconv.Atoi(key)
		if err != nil {
			parallelNP.Panic("Json2Partitions", "Error converting key to int: ", err)
		}
		arr[index-1] = value
	}

	return arr
}