module Algo

include("./sgl_seq.jl")
using .Sgl_seq
include("./sgl_par.jl")
using .Sgl_par

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

function run_algo(kk::KamadaKawai, f::Function, name::String, test_id::String, repetitions::Int)
    # --- SETUP --- #
    original = set_original_coords(kk)

    # --- RUN ALGORITHM R times --- #
    avg_time = 0.0
    for i in 1:repetitions
        # --- RESET DATA --- #
        get_original_coords(kk, original)
        
        # --- EXECUTION --- #
        start = Base.time_ns()
        f(kk)
        elapsed = (Base.time_ns() - start) / 1e9
        avg_time += elapsed
    end
    avg_time /= repetitions
    
    # --- OUTPUT --- #
    output_algo(kk, original, avg_time, name, test_id)
    
    # --- RESET DATA --- #
    get_original_coords(kk, original)
end

function algo(kk::KamadaKawai, test_id::String, repetitions::Int)
    run_algo(kk, Sgl_seq.sgl_seq, "sgl_seq", test_id, repetitions)
    run_algo(kk, Sgl_par.sgl_par, "sgl_par", test_id, repetitions)
    
end # algo

end # module