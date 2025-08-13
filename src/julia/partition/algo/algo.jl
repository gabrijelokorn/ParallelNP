module Algo

include("./seq.jl")
using .Seq
include("./sgl_stc.jl")
using .Sgl_stc
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write
include("../../common/file.jl")
using .File

using BenchmarkTools

export algo

function output_algo(result::Vector{Bool}, elapsed, name::String, test_id::String)
	# --- WRITE RESULTS TO FILE --- #
	algoresult = generateFilename(name, test_id, "json")
	writePartitions(algoresult, result)
	# --- WRITE TIME TO FILE --- #
	algotime = generateFilename(name, test_id, "txt")
	writeTime(algotime, elapsed)
end

function run_algo(arr::Vector{Vector{Int64}}, f::Function, name::String, test_id::String, repetitions::Int)
    # --- SETUP --- #
    result = Vector{Bool}(undef, length(arr))

    # --- BENCHMARK --- #
	GC.gc() # Force garbage collection to ensure memory is cleaned up before output
	bench = @benchmark $f($arr) samples=repetitions evals=1

    # Get median execution time in seconds
    avg_time = median(bench).time / 1e9

    # Run once to get the actual result to save
    result = f(arr)

    output_algo(result, avg_time, name, test_id)
end


function algo(arr::Vector{Vector{Int64}}, test_id::String, repetitions::Int)
	run_algo(arr, Seq.seq, "seq", test_id, repetitions)
	# run_algo(arr, Sgl_stc.sgl_stc, "sgl_stc", test_id, repetitions)
end # algo

end # module
