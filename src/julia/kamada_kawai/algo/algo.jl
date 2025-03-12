module Algo

include("./seq.jl")
using .Seq
include("./par.jl")
using .Par

using ..Kamada_Kawai2csv
using ..Kamada_Kawai

include("../../common/write.jl")
using .Write
include("../../common/file.jl")
using .File

export algo

function echo(result::Vector{Vector{Coord}}, elapsed::Float64, algo::String, num::String, verbose::Bool)
    if !verbose
        return
    end

    algoresult = generateFilename(algo, num, "csv")
    writeVertices(result, algoresult)

    time = generateFilename(algo, num, "txt")
    writeTime(time, elapsed)

end # echo

function algo(kk::KamadaKawai, num::String, verbose::Bool)
    # Sequential
    start_seq = Base.time_ns()
    result = Seq.seq(kk)
    end_seq = Base.time_ns()
    echo(result, (end_seq - start_seq) / 1.0e9, "seq", num, verbose)

    # Parallel
    start_par = Base.time_ns()
    result = Par.par(kk)
    end_par = Base.time_ns()
    echo(result, (end_par - start_par) / 1.0e9, "par", num, verbose)
end # algo

end # module