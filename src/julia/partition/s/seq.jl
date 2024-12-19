module Seq

export small_seq

function small_sum_seq(arr::Vector{Int64}, size::Int, index::Int64) 
    sum = 0;

    for i in 1:size
        if index & (1 << (i - 1)) != 0
            sum += arr[i]
        end
    end

    return sum
end # small_sum_seq

function small_seq(arr::Vector{Vector{Int64}})
    # an array of bools
    result = Vector{Bool}(undef, length(arr))

    for i in 1:length(arr)
        result[i] = false
        size = length(arr[i])

        combs = 1 << (size - 1)
        all = (1 << size) - 1

        problem_sum = small_sum_seq(arr[i], size, all)
        if problem_sum % 2 != 0
            continue
        end
        half_sum = problem_sum / 2

        for j in 1:combs
            sum = small_sum_seq(arr[i], size, j)
            if sum == half_sum
                result[i] = true
                break
            end
        end
    end

    return result
end


end # module