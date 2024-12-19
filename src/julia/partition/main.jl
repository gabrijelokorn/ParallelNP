# Import a library for argument parsing
using ArgParse
using JSON

include("l/large.jl")
using .Large
include("s/small.jl")
using .Small
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
        help = "Path to the sequential output file"
        arg_type = String

        "-y"
        help = "Path to the parallel output file"
        arg_type = String

        "-m"
        help = "Path to the time output file for sequential"
        arg_type = String

        "-n"
        help = "Path to the time output file for parallel"
        arg_type = String

        "-v"
        help = "Enable verbose output"
        arg_type = Bool
        default = false

        "-l"
        help = "Use the partitioning algorithm for large sets"
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
    l = get(parsed_args, "l", false)

    # json test -> partitions
    data = JSON.parsefile(test)
    arr = json2partitions(data)

    if l
        Large.large(arr, verbose, outS, outP, outST, outPT)
    else
        Small.small(arr, verbose, outS, outP, outST, outPT)
    end
end

# Run the main function
main()
