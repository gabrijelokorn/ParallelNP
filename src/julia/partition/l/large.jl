module Large

include("./seq.jl")
using .Seq
include("./par.jl")
using .Par
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write
using Dates

export large
function large(arr::Vector{Vector{Int64}}, verbose::Bool, outS::String, outP::String, outST::String, outPT::String)
    # Sequential
    start_seq = Base.time_ns()
    resultS = Seq.large_seq(arr[1])
    end_seq = Base.time_ns()
    
    # Parallel
    start_par = Base.time_ns()
    resultP = Par.large_par(arr[1])
    end_par = Base.time_ns()
    
    if verbose
        fileS = open(outS, "w")
        partitions2json(fileS, resultS)
        close(fileS)
        timeS = open(outST, "w")
        writeTime(timeS, (end_seq - start_seq) / 1e9) # Convert to seconds
        close(timeS)

        fileP = open(outP, "w")
        partitions2json(fileP, resultP)
        close(fileP)
        timeP = open(outPT, "w")
        writeTime(timeP, (end_par - start_par) / 1e9) # Convert to seconds
        close(timeP)
    end

end # large

end # module