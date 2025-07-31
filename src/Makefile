# #################### ParalelNP Entry Point ################## #
# This Makefile is an entry point of the ParalelNP project. 	#
# It is used to to automate the process of					 	#
# compiling, measuring and resulting the program in all 		#
# 3 languages (c, go, julia)									#
# ############################################################# #

.PHONY: all clean compile run c julia go check
all: clean compile run check


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
run: run_c run_go run_julia
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
# @xdg-open ../views/check.html
### --- ### --- ### --- ###



### --- Partition --- ###
pp:
	@echo -e "##########################################\n    |-> Partition problem $(WD)"
	$(MAKE) -C c c_partition
	$(MAKE) -C go go_partition
	$(MAKE) -C julia julia_partition
	@echo -e "##########################################\n\n"
### --- ### --- ### --- ###



### --- Kamada Kawai --- ###
kk:
	@echo -e "##########################################\n    |-> Kamada Kawai problem $(WD)"
#	$(MAKE) -C c c_kamada_kawai
#	$(MAKE) -C go go_kamada_kawai
	$(MAKE) -C julia julia_kamada_kawai
	@echo -e "##########################################\n\n"
### --- ### --- ### --- ###


### --- Kamada Kawai --- ###
kamada_kawai:
	@if [ -z "$(S)" ] || [ -z "$(E)" ]; then \
		echo "Processing all files"; \
		for case in ../tests/kamada_kawai/*.json; do \
			inPoints=../tests/kamada_kawai/solutions/points$$(basename $$case .json).csv; \
			inCoords=../tests/kamada_kawai/solutions/coords$$(basename $$case .json).csv; \
			inEdges=../tests/kamada_kawai/solutions/edges$$(basename $$case .json).csv; \
			outVideo=../views/$$(basename $$case .json).avi; \
			echo "Generating video $$outVideo"; \
			matlab -nodisplay -nosplash -nodesktop -r "addpath('.'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
		done; \
	else \
		echo "Processing range $(S) to $(E)"; \
		for i in $(shell seq $(S) $(E)); do \
			case=../tests/kamada_kawai/$$(printf "%02d" $$i).json; \
			inPoints=../tests/kamada_kawai/solutions/points$$(printf "%02d" $$i).csv; \
			inCoords=../tests/kamada_kawai/solutions/coords$$(printf "%02d" $$i).csv; \
			inEdges=../tests/kamada_kawai/solutions/edges$$(printf "%02d" $$i).csv; \
			outVideo=../views/$$(printf "%02d" $$i).avi; \
			echo "Generating video $$outVideo"; \
			matlab -nodisplay -nosplash -nodesktop -r "addpath('.'); KamadaKawai('$$inPoints', '$$inCoords', '$$inEdges', '$$outVideo'); exit;" | tail -n +11; \
		done; \
	fi
### --- ### --- ### --- ###
