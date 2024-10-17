############# ParalelNP Entry Point #############
# This Makefile is the entry point for the ParalelNP project.
# It is used to to automate the process of
# compiling, running and testing the program in all 
# 3 languages (C, Julia, Golang).
#################################################

.PHONY: all clean compile test run c julia golang
all: compile run test

# VERBOSE indicates that the program should print results
# into sibling files
# Default value is 1
VERBOSE ?= 1


### --- COMPILE --- ###
compile_c:
	$(MAKE) -C c compile VERBOSE=$(VERBOSE)
compile_julia:
	$(MAKE) -C julia compile VERBOSE=$(VERBOSE)
compile_golang:
	$(MAKE) -C golang compile VERBOSE=$(VERBOSE)
compile: compile_c compile_julia compile_golang
### --- ### --- ### --- ###



### --- RUN --- ###
run_c:
	$(MAKE) -C c run VERBOSE=$(VERBOSE)
run_julia:
	$(MAKE) -C julia run VERBOSE=$(VERBOSE)
run_golang:
	$(MAKE) -C golang run VERBOSE=$(VERBOSE)
run: run_c run_julia run_golang
### --- ### --- ### --- ###



### --- TEST --- ###
test_c:
	echo testing c
test_julia:
	echo testing julia
test_golang:
	echo testing golang
test: test_c test_julia test_golang
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






# This used to be to create a video of the algorithm!
# outVideo=output$$(basename $$case .txt).avi; \
# 		if [ "$(VERBOSE)" = "1" ]; then \
# 			matlab -nodisplay -nosplash -nodesktop -r "addpath('../../../'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
# 		fi; \