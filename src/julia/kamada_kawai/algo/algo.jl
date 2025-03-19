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

function rewindVertices(kk:: KamadaKawai, vertices::Vector{Coord})
    for i in 1:length(vertices)
        kk.coords[i].x = vertices[i].x
        kk.coords[i].y = vertices[i].y
    end
end # rewindVertices

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
    original = deepcopy(kk.coords)
    
    run_with_timeout(kk, Seq.seq, verbose, "seq", num)
    rewindVertices(kk, original)

    run_with_timeout(kk, Par.par, verbose, "par", num)
    rewindVertices(kk, original)
end # algo

end # module