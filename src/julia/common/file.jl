module File

export generateFilename

function generateFilename(algo::String, num::String, postfix::String)
    filename = "algo/" * algo * num * "." * postfix

    return filename
end # generateFilename

end # module

