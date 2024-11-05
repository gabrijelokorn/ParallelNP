############# ParalelNP Entry Point #############
# This Makefile is the entry point for the ParalelNP project.
# It is used to to automate the process of
# compiling, measuring and resulting the program in all 
# 3 languages (C, Julia, Golang).
#################################################

.PHONY: all clean compile result measure c julia golang
all: compile measure result check


### --- COMPILE --- ###
compile_c:
	$(MAKE) -C c compile
compile_julia:
	$(MAKE) -C julia compile
compile_golang:
	$(MAKE) -C golang compile
compile: compile_c compile_julia compile_golang
### --- ### --- ### --- ###



### --- MEASURE --- ###
measure_c:
	$(MAKE) -C c measure
measure_julia:
	$(MAKE) -C julia measure
measure_golang:
	$(MAKE) -C golang measure
measure: measure_c measure_julia measure_golang
### --- ### --- ### --- ###



### --- Kamada Kawai --- ###
kamada_kawai:
	@for case in tests/Kamada_Kawai/*.json; do \
		inPoints=c/sequential/Kamada_Kawai/points$$(basename $$case .json).csv; \
		inCoords=c/sequential/Kamada_Kawai/coords$$(basename $$case .json).csv; \
		inEdges=c/sequential/Kamada_Kawai/edges$$(basename $$case .json).csv; \
		outVideo=views/output$$(basename $$case .json).avi; \
		echo "Generating video $$outVideo"; \
		matlab -nodisplay -nosplash -nodesktop -r "addpath('views/'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
	done
### --- ### --- ### --- ###



### --- RESULT --- ###
result_c:
	$(MAKE) -C c result
result_julia:
	$(MAKE) -C julia result
result_golang:
	$(MAKE) -C golang result

result: result_c result_julia result_golang kamada_kawai
### --- ### --- ### --- ###



### --- COMPARE --- ###
check:
	@node views/check.js
	@xdg-open views/check.html\

### --- ### --- ### --- ###



### --- ### Compile measure result in seperate languages ### --- ###
c: compile_c measure_c result_c
julia: compile_julia measure_julia result_julia
golang: compile_golang measure_golang result_golang
### --- ### --- ### --- ### --- ### --- ### --- ###



### --- ### Clean the program in all languages ### --- ###
clean:
	$(MAKE) -C c clean
#	$(MAKE) -C golang clean
#	$(MAKE) -C julia clean
### --- ### --- ### --- ### --- ### --- ### --- ###
