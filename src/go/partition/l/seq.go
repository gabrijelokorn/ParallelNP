package large

func setSum(arr []int) int {
	var sum int = 0
	for i := 0; i < len(arr); i++ {
		sum += arr[i]
	}
	return sum
}

func Seq(arr []int) bool {
	var size int = len(arr)
	var index int64 = 1 << (size - 1)

	for i := int64(0); i < index; i++ {
		array1 := make([]int, size)
		var index1 = 0
		array2 := make([]int, size)
		var index2 = 0

		for j := 0; j < size; j++ {
			if (i & (1 << j)) != 0 {
				array1[index1] = arr[j]
				index1++
			} else {
				array2[index2] = arr[j]
				index2++
			}
		}

		var sum1 int = setSum(array1)
		var sum2 int = setSum(array2)

		if sum1 == sum2 {
			return true
		}
	}

	return false
}
