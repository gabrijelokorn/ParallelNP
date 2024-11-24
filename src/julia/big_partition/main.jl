# Import a library for argument parsing
using ArgParse
using JSON

include("seq.jl")
using .Seq

include("../lib/kamada_kawai.jl")
using .Kamada_Kawai
include("../lib/file.jl")
using .Out
include("../lib/print.jl")
using .Print

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
    verbose = get(parsed_args, "v", false)

    data = JSON.parsefile(test)
    
    arr = Vector{Vector{Int64}}(undef, length(data))
    for (key, value) in data
        index = parse(Int, key)
        arr[index] = value
    end
    
    resultS = fill(false, length(data))
    for i in 1:length(data)
        resultS[i] = Seq.seq(arr[i])
    end


    resultP = fill(false, length(data))

    if verbose
        file = Out.openFile(outS)
        fOutJsonArray(file, resultS)
    end

end

# Run the main function
main()
