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
    verbose = get(parsed_args, "v", false)
    num = get(parsed_args, "x", "")

    # json test -> partitions
    data = JSON.parsefile(test)
    arr = json2partitions(data)

    algo(arr, verbose, num)
end

# Run the main function
main()
