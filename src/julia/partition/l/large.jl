module Large

include("./seq.jl")
using .Seq
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write
using Dates

export large
function large(arr::Vector{Vector{Int64}}, verbose::Bool, outS::String, outP::String, outST::String, outPT::String)
    # Sequential
    start_seq = Dates.now()
    resultS = Seq.large_seq(arr[1])
    end_seq = Dates.now()

    if verbose
        fileS = open(outS, "w")
        partitions2json(fileS, resultS)
        close(fileS)
        timeS = open(outST, "w")
        writeTime(timeS, end_seq - start_seq)
        close(timeS)

    end

end # large

end # module