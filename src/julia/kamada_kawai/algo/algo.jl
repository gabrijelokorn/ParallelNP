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

function run_with_timeout(kk::KamadaKawai, f::Function, verbose::Bool, name::String, num::String)
    start = Base.time_ns()
    result = f(kk)
    elapsed = (Base.time_ns() - start) / 1e9
    
    if !verbose
        return
    end

    algoresult = generateFilename(name, num, "csv")
    writeVertices(result, algoresult)

    algotime = generateFilename(name, num, "txt")
    writeTime(algotime, elapsed)
end

function algo(kk::KamadaKawai, verbose::Bool, num::String)
    run_with_timeout(kk, Seq.seq, verbose, "seq", num)
    run_with_timeout(kk, Par.par, verbose, "par", num)
end # algo

end # module