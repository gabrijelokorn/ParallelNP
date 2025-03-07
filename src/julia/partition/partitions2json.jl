module Partitions2Json

using JSON

export partitions2json
function partitions2json(file, arr::Vector{Bool})
    jsonString = JSON.json(arr)
    write(file, jsonString)
end # partitions2json

export writePartitions
function writePartitions(file, arr::Vector{Bool})
    partitions2json(file, arr)
end

end # module

