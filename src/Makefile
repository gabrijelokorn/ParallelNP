############# ParalelNP Entry Point #############
# This Makefile is the entry point for the ParalelNP project.
# It is used to to automate the process of
# compiling, measuring and resulting the program in all 
# 3 languages (c, go, julia)
#################################################

.PHONY: all clean compile run c julia go check
all: compile run check


### --- COMPILE --- ###
compile_c:
	$(MAKE) -C c compile
compile_julia:
	$(MAKE) -C julia compile
compile_go:
	$(MAKE) -C go compile
compile: compile_c compile_julia compile_go
### --- ### --- ### --- ###



### --- RUN --- ###
run_c:
	$(MAKE) -C c run
run_julia:
	$(MAKE) -C julia run
run_go:
	$(MAKE) -C go run
run: run_c run_julia run_go
### --- ### --- ### --- ###



### --- ### LANGUAGES ### --- ###
c: compile_c run_c
julia: compile_julia run_julia
go: compile_go run_go
### --- ### ######### ### --- ###



### --- CHECK --- ###
check:
	@node check.js
	@xdg-open ../views/check.html
### --- ### --- ### --- ###



### --- Kamada Kawai --- ###
kamada_kawai:
	@for case in ../tests/kamada_kawai/*.json; do \
		inPoints=../tests/kamada_kawai/solutions/points$$(basename $$case .json).csv; \
		inCoords=../tests/kamada_kawai/solutions/coords$$(basename $$case .json).csv; \
		inEdges=../tests/kamada_kawai/solutions/edges$$(basename $$case .json).csv; \
		outVideo=../views/$$(basename $$case .json).avi; \
		echo "Generating video $$outVideo"; \
		matlab -nodisplay -nosplash -nodesktop -r "addpath('.'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
	done
### --- ### --- ### --- ###



### --- ### Clean the program in all languages ### --- ###
clean:
	$(MAKE) -C c clean
	$(MAKE) -C go clean
#	$(MAKE) -C julia clean
### --- ### --- ### --- ### --- ### --- ### --- ###
