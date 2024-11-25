package parallelNP

func Panic(filename string, errorMsg string, err error) {
	panic("\n->->->\n" + filename + " )-:\n" + errorMsg + err.Error() + "\n<-<-<-\n")
}

func IOError(filename string, errorMsg string, err error) {
	Panic(filename, errorMsg, err)
}

func UnmarshalError(filename string, errorMsg string, err error) {
	Panic(filename, errorMsg, err)
}