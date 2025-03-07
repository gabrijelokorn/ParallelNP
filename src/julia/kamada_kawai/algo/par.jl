module Par

export par

using ...Kamada_Kawai

function derivative_x_m_par(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for

    return sum
end # derivative_x_m_par

function derivative_y_m_par(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for

    return sum
end # derivative_y_m_par

function derivative_xx_m_par(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_y^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for

    return sum
end # derivative_xx_m_par

function derivative_yy_m_par(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_x^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for

    return sum
end # derivative_yy_m_par

function derivative_xy_m_par(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (kk.l_ij[index, i] * dist_x * dist_y) / (dist_x^2 + dist_y^2)^(Float64(1.5))
        end # if
    end # for

    return sum
end # derivative_xy_m_par

function get_delta_y_par(
    derivative_x_m_par::Float64,
    derivative_y_m_par::Float64,
    derivative_xx_m_par::Float64,
    derivative_yy_m_par::Float64,
    derivative_xy_m_par::Float64
)
    return (-(derivative_xy_m_par * derivative_x_m_par) + (derivative_xx_m_par * derivative_y_m_par)) / (-(derivative_xx_m_par * derivative_yy_m_par) + derivative_xy_m_par^2)
end # get_delta_y_par

function get_delta_x_par(
    derivative_y_m_par::Float64,
    derivative_yy_m_par::Float64,
    derivative_xy_m_par::Float64,
    delta_y::Float64
)
    return (-(derivative_y_m_par) - (derivative_yy_m_par * delta_y)) / derivative_xy_m_par
end # get_delta_x_par

function delta_m_par(derivative_x_m_par::Float64, derivative_y_m_par::Float64)
    return (derivative_x_m_par^2 + derivative_y_m_par^2)^Float64(0.5)
end # delta_m_par

function calculate_delta_par(kk::KamadaKawai, index::Int)
    derivative_x = derivative_x_m_par(kk, index)
    derivative_y = derivative_y_m_par(kk, index)

    return delta_m_par(derivative_x, derivative_y)
end # calculate_delta_par

function calculate_deltas_par(kk::KamadaKawai)
    deltas = Vector{Float64}(undef, kk.n)

    Threads.@threads for i in eachindex(kk.n)
        deltas[i] = calculate_delta_par(kk, i)
    end # for

    return deltas
end # calculate_deltas_par

function get_max_delta_m_index_par(deltas::Vector{Float64}, epsilon::Float64)
    max = -1.0
    index = -1

    for i in 1:length(deltas)
        delta = deltas[i]
        if delta > max
            max = delta
            if delta > epsilon
                index = i
            end # if
        end # if
    end # for

    return index
end # get_max_delta_m_index_par

function compute_derivatives_par(kk::KamadaKawai, index::Int)
    Threads.@spawn d_x_m = derivative_x_m_par(kk, index)
    Threads.@spawn d_y_m = derivative_y_m_par(kk, index)
    Threads.@spawn d_xx_m = derivative_xx_m_par(kk, index)
    Threads.@spawn d_yy_m = derivative_yy_m_par(kk, index)
    Threads.@spawn d_xy_m = derivative_xy_m_par(kk, index)
    return fetch(d_x_m), fetch(d_y_m), fetch(d_xx_m), fetch(d_yy_m), fetch(d_xy_m)
end

function par(kk::KamadaKawai)
    states = Vector{Vector{Coord}}()
    # copy the coordinates into the first element of states
    push!(states, deepcopy(kk.coords))

    deltas = calculate_deltas_par(kk)
    max_delta_m_par_index = get_max_delta_m_index_par(deltas, kk.epsilon)

    while max_delta_m_par_index != -1
        while deltas[max_delta_m_par_index] > kk.epsilon
            d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = compute_derivatives_par(kk, max_delta_m_par_index)

            delta_y = get_delta_y_par(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
            delta_x = get_delta_x_par(d_y_m, d_yy_m, d_xy_m, delta_y)

            kk.coords[max_delta_m_par_index].x += delta_x
            kk.coords[max_delta_m_par_index].y += delta_y

            deltas[max_delta_m_par_index] = calculate_delta_par(kk, max_delta_m_par_index)
        end # while

        deltas = calculate_deltas_par(kk)
        max_delta_m_par_index = get_max_delta_m_index_par(deltas, kk.epsilon)

    end # while
    push!(states, deepcopy(kk.coords))

    return states
end # par

end # module