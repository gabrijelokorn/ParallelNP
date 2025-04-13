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

        "-x"
        help = "Enumeration of testcase"
        arg_type = String
    end
    # Parse the arguments
    parsed_args = parse_args(ARGS, s)

    test_path = get(parsed_args, "t", "")
    test_id = get(parsed_args, "x", "")

    data = JSON.parsefile(test_path)

    kk = KamadaKawai(
        data["coords"],
        data["edges"],
        Float64(data["K"]),
        Float64(data["epsilon"]),
        Float64(data["display"]),
        Int(data["limit"])
    )

    algo(kk, test_id)
end

# Run the main function
main()
