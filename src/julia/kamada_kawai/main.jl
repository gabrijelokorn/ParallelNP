using ArgParse
using JSON

include("../lib/kamada_kawai.jl")
using .Kamada_Kawai

include("seq.jl")
using .Seq

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

    kk = Kamada_Kawai.KamadaKawai(data["coords"], data["edges"], Float64(data["K"]), Float64(data["epsilon"]), Float64(data["display"]))
    resultS = seq(kk)

    if verbose
        file = Out.openFile(outS)
        Print.fOutStates(file, resultS)
    end
end

# Run the main function
main()
