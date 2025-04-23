module File

export generateFilename

function generateFilename(algo::String, num::String, postfix::String)
    nThreads = Threads.nthreads()
    filename = "algo/$(nThreads)/$(algo)$(num).$(postfix)"
    return filename
end


end # module

