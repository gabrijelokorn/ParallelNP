module Seq

export seq

function seq(arr::Vector{Int64})
    size = length(arr)
    index::Int64 = 1 << (size - 1)

    for i in 1:index
        array1 = Vector{Int64}(undef, size)
        index1 = 1  # Start from 1
        array2 = Vector{Int64}(undef, size)
        index2 = 1  # Start from 1

        for j in 1:size
            if i & (1 << (j - 1)) != 0  # Adjust bitmask indexing
                array1[index1] = arr[j]
                index1 += 1
            else
                array2[index2] = arr[j]
                index2 += 1
            end
        end

        # Compute sums only for valid parts of the arrays
        sum1 = sum(array1[1:index1-1])
        sum2 = sum(array2[1:index2-1])

        if sum1 == sum2
            return true
        end
    end
    return false
end


end # module