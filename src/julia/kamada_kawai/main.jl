using ArgParse
using JSON

include("./kamada_kawai.jl")
using .Kamada_Kawai
include("./kamada_kawai2csv.jl")
using .Kamada_Kawai2csv
include("../common/write.jl")
using .Write
using Dates

include("seq.jl")
using .Seq
include("par.jl")
using .Par

function main()
    # Define the arguments you expect
    s = ArgParseSettings()
    @add_arg_table! s begin
        "-t"
        help = "Path to the test file"
        arg_type = String
        required = true

        "-x"
        help = "Path to the sequential output file"
        arg_type = String

        "-m"
        help = "Path to the time output file for sequential"
        arg_type = String

        "-n"
        help = "Path to the time output file for parallel"
        arg_type = String

        "-y"
        help = "Path to the parallel output file"
        arg_type = String

        "-v"
        help = "Enable verbose output"
        arg_type = Bool
        default = false
    end
    # Parse the arguments
    parsed_args = parse_args(ARGS, s)

    test = get(parsed_args, "t", "")
    outS = get(parsed_args, "x", "")
    outP = get(parsed_args, "y", "")
    outST = get(parsed_args, "m", "")
    outPT = get(parsed_args, "n", "")
    verbose = get(parsed_args, "v", false)

    data = JSON.parsefile(test)

    kk = KamadaKawai(
        data["coords"],
        data["edges"],
        Float64(data["K"]),
        Float64(data["epsilon"]),
        Float64(data["display"])
    )

    # Sequential
    start_seq = Base.time_ns()
    resultS = seq(kk)
    end_seq = Base.time_ns()
    
    # Parallel
    start_par = Base.time_ns()
    resultP = Par.par(kk)
    end_par = Base.time_ns()

    if verbose
        fileS = open(outS, "w")
        WriteVertices(fileS, resultS)
        close(fileS)
        timeS = open(outST, "w")
        writeTime(timeS, (end_seq - start_seq) / 1e9) # Convert to seconds
        close(timeS)

        fileP = open(outP, "w")
        WriteVertices(fileP, resultP)
        close(fileP)
        timeP = open(outPT, "w")
        writeTime(timeP, (end_par - start_par) / 1e9) # Convert to seconds
        close(timeP)
    end
end

# Run the main function
main()
