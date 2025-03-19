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

function run_with_timeout(arr::Vector{Vector{Int64}}, f::Function, verbose::Bool, name::String, num::String)
    start = Base.time_ns()
    result = f(arr)
    elapsed = (Base.time_ns() - start) / 1e9
    
    if !verbose
        return
    end

    algoresult = generateFilename(name, num, "json")
    writePartitions(algoresult, result)

    algotime = generateFilename(name, num, "txt")
    writeTime(algotime, elapsed)
end

function algo(arr::Vector{Vector{Int64}}, verbose::Bool, num::String)
    run_with_timeout(arr, Seq.seq, verbose, "seq", num)
    run_with_timeout(arr, Par.par, verbose, "par", num)
end # algo

end # module