module Seq

export large_seq

function large_sum_seq(arr::Vector{Int64}, size::Int, index::Int64) 
    sum = 0;

    for i in 1:size
        if index & (1 << (i - 1)) != 0
            sum += arr[i]
        end
    end

    return sum
end # large_sum_seq

function large_seq(arr::Vector{Int64})
    size = length(arr)
    combs = 1 << (size - 1)
    all = (1 << size) - 1

    problem_sum = large_sum_seq(arr, size, all)
    if problem_sum % 2 != 0
        return [false]
    end
    half_sum = problem_sum / 2

    for i in 1:combs
        sum = large_sum_seq(arr, size, i)
        if sum == half_sum
            return [true]
        end
    end

    return [false]
end


end # module