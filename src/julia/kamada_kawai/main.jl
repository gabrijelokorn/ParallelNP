using ArgParse
using JSON

include("./kamada_kawai.jl")
using .Kamada_Kawai
include("./kamada_kawai2csv.jl")
using .Kamada_Kawai2csv
include("../common/write.jl")
using .Write

include("algo/algo.jl")
using .Algo

using Dates

function main()
    # Define the arguments you expect
    s = ArgParseSettings()
    @add_arg_table! s begin
        "-t"
        help = "Path to the test file"
        arg_type = String
        required = true

        "-n"
        help = "Number of threads"
        arg_type = Int
        default = 1

        "-x"
        help = "Enumeration of testcase"
        arg_type = String

        "-v"
        help = "Enable verbose output"
        arg_type = Bool
        default = false
    end
    # Parse the arguments
    parsed_args = parse_args(ARGS, s)

    test = get(parsed_args, "t", "")
    nThreads = get(parsed_args, "n", 1)
    verbose = get(parsed_args, "v", false)
    num = get(parsed_args, "x", "")

    data = JSON.parsefile(test)

    kk = KamadaKawai(
        data["coords"],
        data["edges"],
        Float64(data["K"]),
        Float64(data["epsilon"]),
        Float64(data["display"])
    )

    algo(kk, nThreads, verbose, num)
end

# Run the main function
main()
