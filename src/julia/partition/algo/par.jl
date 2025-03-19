module Par

export small_par

function sum_par(arr::Vector{Int64}, size::Int, index::Int64) 
    sum = 0;

    for i in 1:size
        if index & (1 << (i - 1)) != 0
            sum += arr[i]
        end
    end

    return sum
end # sum_par

function par(arr::Vector{Vector{Int64}})
    # an array of bools
    result = Vector{Bool}(undef, length(arr))

    Threads.@threads for i in 1:length(arr)
        result[i] = false
        size = length(arr[i])

        numOfCombinations = 1 << (size - 1)
        allNumbersMask = (1 << size) - 1

        problem_sum = sum_par(arr[i], size, allNumbersMask)
        if problem_sum % 2 != 0
            continue
        end
        half_sum = problem_sum / 2

        for j in 1:numOfCombinations
            sum = sum_par(arr[i], size, j)
            if sum == half_sum
                result[i] = true
                break
            end
        end
    end

    return result
end

end # module