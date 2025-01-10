module Small

include("./seq.jl")
using .Seq
include("./par.jl")
using .Par
include("../partitions2json.jl")
using .Partitions2Json
include("../../common/write.jl")
using .Write

export small
function small(arr::Vector{Vector{Int64}}, verbose::Bool, outS::String, outP::String, outST::String, outPT::String)
    # Sequential
    start_seq = Base.time_ns()
    resultS = Seq.small_seq(arr)
    end_seq = Base.time_ns()
    
    # Parallel
    start_par = Base.time_ns()
    resultP = Par.small_par(arr)
    end_par = Base.time_ns()


    if verbose
        file = open(outS, "w")
        partitions2json(file, resultS)
        close(file)
        timeS = open(outST, "w")
        writeTime(timeS, (end_seq - start_seq) / 1e9) # Convert to seconds
        close(timeS)

        file = open(outP, "w")
        partitions2json(file, resultP)
        close(file)
        timeP = open(outPT, "w")
        writeTime(timeP, (end_par - start_par) / 1e9) # Convert to seconds
        close(timeP)
    end

end # small

end # module