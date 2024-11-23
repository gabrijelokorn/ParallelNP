module Print

using JSON

export fOutJsonArray 

function fOutJsonArray(file, arr::Vector{Bool})
    jsonString = JSON.json(arr)
    write(file, jsonString)
end

end # module