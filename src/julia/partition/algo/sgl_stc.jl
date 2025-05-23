module Sgl_stc

include("../partition.jl")
using .Partition
using Base.Threads

function sgl_stc(arr::Vector{Vector{Int64}})
    result = Vector{Bool}(undef, length(arr))

    for i in 1:length(arr)
        result[i] = false
        size = length(arr[i])

        numOfCombinations = 1 << (size - 1)
        allNumbersMask = (1 << size) - 1

        problem_sum = partition_sum(arr[i], size, allNumbersMask)
        if problem_sum % 2 != 0
            continue
        end
        half_problem_sum = problem_sum ÷ 2

        # Shared atomic flag
        found = Threads.Atomic{Bool}(false)

        Threads.@threads for j in 1:numOfCombinations
            # Early exit if already found
            if found[]
                continue
            end

            sum = partition_sum(arr[i], size, j)
            if sum == half_problem_sum
                found[] = true
            end
        end

        result[i] = found[]
    end

    return result
end

end # module