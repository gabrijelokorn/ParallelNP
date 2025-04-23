# Import a library for argument parsing
using ArgParse
using JSON

include("algo/algo.jl")
using .Algo
include("partitions2json.jl")
using .Partitions2Json
include("json2partitions.jl")
using .Json2partitions

function main()
    # Define the arguments you expect
    s = ArgParseSettings()
    @add_arg_table! s begin
        "-t"
        help = "Path to the test file"
        arg_type = String
        required = true

        "-r"
        help = "Number of repetitions"
        arg_type = Int

        "-x"
        help = "Enumeration of testcase"
        arg_type = String
    end

    # Parse the arguments
    parsed_args = parse_args(ARGS, s)

    test_path = get(parsed_args, "t", "")
    repetitions = get(parsed_args, "r", "")
    test_id = get(parsed_args, "x", "")

    # json test -> partitions
    data = JSON.parsefile(test_path)
    arr = json2partitions(data)

    algo(arr, test_id,repetitions)
end

# Run the main function
main()
