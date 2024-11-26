module Small

include("./seq.jl")
using .Seq
include("../partitions2json.jl")
using .Partitions2Json

export small
function small(arr::Vector{Vector{Int64}}, verbose::Bool, outS::String, outP::String)
    # Sequential
    resultS = fill(false, length(arr))
    for i in 1:length(arr)
        resultS[i] = Seq.seq(arr[i])
    end

    if verbose
        file = open(outS, "w")
        partitions2json(file, resultS)
        close(file)
    end

end # small

end # module