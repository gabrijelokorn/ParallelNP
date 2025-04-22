module Mlt_dyn

include("../partition.jl")
using .Partition

function mlt_dyn(arr::Vector{Vector{Int64}})
    # an array of bools
    result = Vector{Bool}(undef, length(arr))

    Threads.@threads for i in 1:length(arr)
        result[i] = false
        size = length(arr[i])

        numOfCombinations = 1 << (size - 1)
        allNumbersMask = (1 << size) - 1

        problem_sum = partition_sum(arr[i], size, allNumbersMask)
        if problem_sum % 2 != 0
            continue
        end
        half_problem_sum = problem_sum / 2

        for j in 1:numOfCombinations
            sum = partition_sum(arr[i], size, j)
            if sum == half_problem_sum
                result[i] = true
                break
            end
        end
    end

    return result
end

end # module