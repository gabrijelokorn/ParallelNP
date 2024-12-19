module Small

include("./seq.jl")
using .Seq
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write
using Dates

export small
function small(arr::Vector{Vector{Int64}}, verbose::Bool, outS::String, outP::String, outST::String, outPT::String)
    # Sequential
    start_seq = Dates.now()
    resultS = Seq.small_seq(arr)
    end_seq = Dates.now()

    if verbose
        file = open(outS, "w")
        partitions2json(file, resultS)
        close(file)
        timeS = open(outST, "w")
        writeTime(timeS, end_seq - start_seq)
        close(timeS)
    end

end # small

end # module