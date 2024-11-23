module Out

export out

function openFile(filename::String)
    return open(filename, "w")
end # openFile

end # module