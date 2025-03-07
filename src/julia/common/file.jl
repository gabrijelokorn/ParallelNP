module File

export parseFilename

function parseFilename(algo::String, num::String, postfix::String)
    filename = "algo/" * algo * num * "." * postfix

    return filename
end # parseFilename

end # module

