package parallelNP

func Panic(filename string, errorMsg string, err error) {
	panic("\n->->->\n" + filename + " )-:\n" + errorMsg + err.Error() + "\n<-<-<-\n")
}
