module Par

using Base.Threads
export large_par

function large_sum_par(arr::Vector{Int64}, size::Int, index::Int64)
    sum = 0

    for i in 1:size
        if index & (1 << (i - 1)) != 0
            sum += arr[i]
        end
    end

    return sum
end # large_sum_par

function large_par(arr::Vector{Int64})
    size = length(arr)
    combs = 1 << (size - 1)
    all = (1 << size) - 1

    problem_sum = large_sum_par(arr, size, all)
    if problem_sum % 2 != 0
        return [false]
    end
    half_sum = problem_sum ÷ 2

    found = Threads.Atomic{Bool}(false)

    Threads.@threads for i in 1:combs
        if found[]
            continue
        end

        sum = large_sum_par(arr, size, i)
        if sum == half_sum
            found[] = true
        end
    end

    return [found[]]
end # large_par

end # module
