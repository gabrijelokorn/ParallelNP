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

function echo(result::Vector{Bool}, elapsed::Float64, algo::String, num::String, verbose::Bool)
    if !verbose
        return
    end

    algoresult = generateFilename(algo, num, "json")
    writePartitions(algoresult, result)

    time = generateFilename(algo, num, "txt")
    writeTime(time, elapsed)
    
end # echo

function algo(arr::Vector{Vector{Int64}}, num::String, verbose::Bool)
    # Sequential
    start_seq = Base.time_ns()
    result = Seq.seq(arr)
    end_seq = Base.time_ns()
    echo(result, (end_seq - start_seq) / 1e9, "seq", num, verbose)
    
    # Parallel
    start_par = Base.time_ns()
    resultP = Par.par(arr)
    end_par = Base.time_ns()
    echo(resultP, (end_par - start_par) / 1e9, "par", num, verbose)

end # Algo

end # module