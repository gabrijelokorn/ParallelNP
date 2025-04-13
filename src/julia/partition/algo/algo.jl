module Algo

include("./seq.jl")
using .Seq
include("./par.jl")
using .Par
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write
include("../../common/file.jl")
using .File

export algo

function output_algo(result::Vector{Bool}, elapsed, name::String, test_id::String)
    # --- WRITE RESULTS TO FILE --- #
    algoresult = generateFilename(name, test_id, "json")
    writePartitions(algoresult, result)
    # --- WRITE TIME TO FILE --- #
    algotime = generateFilename(name, test_id, "txt")
    writeTime(algotime, elapsed)
end

function run_algo(arr::Vector{Vector{Int64}}, f::Function, name::String, test_id::String)
    # --- EXECTUTION --- #
    start = Base.time_ns()
    result = f(arr)
    elapsed = (Base.time_ns() - start) / 1e9

    output_algo(result, elapsed, name, test_id)
end

function algo(arr::Vector{Vector{Int64}}, test_id::String)
    run_algo(arr, Seq.seq, "seq", test_id)
    run_algo(arr, Par.par, "par", test_id)
end # algo

end # module