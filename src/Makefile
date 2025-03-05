# #################### ParalelNP Entry Point ################## #
# This Makefile is an entry point of the ParalelNP project. 	#
# It is used to to automate the process of					 	#
# compiling, measuring and resulting the program in all 		#
# 3 languages (c, go, julia)									#
# ############################################################# #

.PHONY: all clean compile run c julia go check
all: clean compile run check

export OMP_CANCELLATION=true



### --- COMPILE --- ###
compile_c:
	$(MAKE) -C c compile
compile_go:
	$(MAKE) -C go compile
compile_julia:
	$(MAKE) -C julia compile
compile: compile_c  compile_go compile_julia
### --- ### --- ### --- ###



### --- RUN --- ###
run_c:
	$(MAKE) -C c run
run_go:
	$(MAKE) -C go run
run_julia:
	$(MAKE) -C julia run
run: run_c run_julia run_go
### --- ### --- ### --- ###



### --- CLEAN --- ###
clean_c:
	$(MAKE) -C c clean
clean_go:
	$(MAKE) -C go clean
clean_julia:
	$(MAKE) -C julia clean
clean: clean_c clean_go clean_julia
### --- ### --- ### --- ###



### --- ### LANGUAGES ### --- ###
c: clean_c compile_c run_c
go: clean_go compile_go run_go
julia: clean_julia compile_julia run_julia
### --- ### ######### ### --- ###



### --- CHECK --- ###
check:
	@echo "Check out the results in views/check.html"
	@echo ""
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
