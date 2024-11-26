using ArgParse
using JSON

include("./kamada_kawai.jl")
using .Kamada_Kawai
include("./kamada_kawai2csv.jl")
using .Kamada_Kawai2csv

include("seq.jl")
using .Seq

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

    kk = KamadaKawai(
        data["coords"],
        data["edges"],
        Float64(data["K"]),
        Float64(data["epsilon"]),
        Float64(data["display"])
    )

    resultS = seq(kk)

    if verbose
        file = open(outS, "w")
        WriteVertices(file, resultS)
        close(file)
    end
end

# Run the main function
main()
