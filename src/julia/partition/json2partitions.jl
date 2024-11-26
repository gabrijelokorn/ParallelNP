module Json2partitions

export json2partitions
function json2partitions(data::Dict{String, Any})
    arr = Vector{Vector{Int64}}(undef, length(data))
    for (key, value) in data
        index = parse(Int, key)
        arr[index] = value
    end

    return arr
end # json2partitions

end # module

