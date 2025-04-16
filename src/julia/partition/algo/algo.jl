module Algo

include("./seq.jl")
using .Seq
include("./mlt_dyn.jl")
using .Mlt_dyn
include("./mlt_stc.jl")
using .Mlt_stc
include("./sgl_dyn.jl")
using .Sgl_dyn
include("./sgl_stc.jl")
using .Sgl_stc
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
    run_algo(arr, Mlt_dyn.mlt_dyn, "mlt_dyn", test_id)
    run_algo(arr, Mlt_stc.mlt_stc, "mlt_stc", test_id)
    run_algo(arr, Sgl_dyn.sgl_dyn, "sgl_dyn", test_id)
    run_algo(arr, Sgl_stc.sgl_stc, "sgl_stc", test_id)
end # algo

end # module