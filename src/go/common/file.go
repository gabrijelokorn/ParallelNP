package parallelNP

func GenerateFilename(algo string, num string, ext string) string {
	return "algo" + "/" + algo + num + "." + ext
}
