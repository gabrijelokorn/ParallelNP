module Partition

export partition_sum
function partition_sum(arr::Vector{Int64}, size::Int, index::Int64) 
    sum = 0;

    for i in 1:size
        if index & (1 << (i - 1)) != 0
            sum += arr[i]
        end
    end

    return sum
end # partition_sum

end # module

