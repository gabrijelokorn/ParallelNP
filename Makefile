############# ParalelNP Entry Point #############
# This Makefile is the entry point for the ParalelNP project.
# It is used to to automate the process of
# compiling, running and testing the program in all 
# 3 languages (C, Julia, Golang).
#################################################

.PHONY: all clean compile test run c julia golang
all: compile run test


### --- COMPILE --- ###
compile_c:
	$(MAKE) -C c compile
compile_julia:
	$(MAKE) -C julia compile
compile_golang:
	$(MAKE) -C golang compile
compile: compile_c compile_julia compile_golang
### --- ### --- ### --- ###



### --- RUN --- ###
run_c:
	$(MAKE) -C c run
run_julia:
	$(MAKE) -C julia run
run_golang:
	$(MAKE) -C golang run
run: run_c run_julia run_golang
### --- ### --- ### --- ###



### --- TEST --- ###
test_c:
	$(MAKE) -C c test
	node ./views/report.js
test_julia:
	$(MAKE) -C julia test
	node ./views/report.js
test_golang:
	$(MAKE) -C golang test
	node ./views/report.js

test: test_c test_julia test_golang
	node ./views/report.js
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



### --- ### Compile Run Test in seperate languages ### --- ###
c: compile_c run_c test_c
julia: compile_julia run_julia test_julia
golang: compile_golang run_golang test_golang
### --- ### --- ### --- ### --- ### --- ### --- ###



### --- ### Clean the program in all languages ### --- ###
clean:
	$(MAKE) -C c clean
#	$(MAKE) -C golang clean
#	$(MAKE) -C julia clean
### --- ### --- ### --- ### --- ### --- ### --- ###
