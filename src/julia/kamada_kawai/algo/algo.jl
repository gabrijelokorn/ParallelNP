module Algo

include("./sgl_seq.jl")
using .Sgl_seq
include("./sgl_par.jl")
using .Sgl_par
include("./mlt_seq.jl")
using .Mlt_seq
include("./mlt_par.jl")
using .Mlt_par

using ..Kamada_Kawai2csv
using ..Kamada_Kawai

include("../../common/write.jl")
using .Write
include("../../common/file.jl")
using .File

export algo

function output_algo(kk::KamadaKawai, original::Vector{Coord}, elapsed, name::String, test_id::String)
    # --- WRITE RESULTS TO FILE --- #
    algoresult = generateFilename(name, test_id, "csv")
    algoresult_fp = open(algoresult, "w")
    writeState(algoresult_fp, original)
    writeState(algoresult_fp, kk.coords)
    close(algoresult_fp)
    # --- WRITE TIME TO FILE --- #
    algotime = generateFilename(name, test_id, "txt")
    writeTime(algotime, elapsed)
end

function run_algo(kk::KamadaKawai, f::Function, name::String, test_id::String)
    # --- SETUP --- #
    original = set_original_coords(kk)

    # --- EXECTUTION --- #
    start = Base.time_ns()
    f(kk)
    elapsed = (Base.time_ns() - start) / 1e9
    
    output_algo(kk, original, elapsed, name, test_id)

    # --- RESET DATA --- #
    get_original_coords(kk, original)
end

function algo(kk::KamadaKawai, test_id::String)
    run_algo(kk, Sgl_seq.sgl_seq, "sgl_seq", test_id)
    run_algo(kk, Sgl_par.sgl_par, "sgl_par", test_id)
    run_algo(kk, Mlt_seq.mlt_seq, "mlt_seq", test_id)
    run_algo(kk, Mlt_par.mlt_par, "mlt_par", test_id)
    
end # algo

end # module