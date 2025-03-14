module Seq

export seq

using ...Kamada_Kawai

function derivative_x_m_seq(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for
    
    return sum
end # derivative_x_m_seq

function derivative_y_m_seq(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for
    
    return sum
end # derivative_y_m_seq

function derivative_xx_m_seq(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_y^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for
    
    return sum
end # derivative_xx_m_seq

function derivative_yy_m_seq(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_x^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for
    
    return sum
end # derivative_yy_m_seq

function derivative_xy_m_seq(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (kk.l_ij[index, i] * dist_x * dist_y) / (dist_x^2 + dist_y^2)^(Float64(1.5))
        end # if
    end # for
    
    return sum
end # derivative_xy_m_seq

function get_delta_y_seq(
    derivative_x_m_seq::Float64,
    derivative_y_m_seq::Float64,
    derivative_xx_m_seq::Float64,
    derivative_yy_m_seq::Float64,
    derivative_xy_m_seq::Float64
)
    return (-(derivative_xy_m_seq * derivative_x_m_seq) + (derivative_xx_m_seq * derivative_y_m_seq)) / (-(derivative_xx_m_seq * derivative_yy_m_seq) + derivative_xy_m_seq^2)
end # get_delta_y_seq

function get_delta_x_seq(
    derivative_y_m_seq::Float64,
    derivative_yy_m_seq::Float64,
    derivative_xy_m_seq::Float64,
    delta_y::Float64
)
    return (-(derivative_y_m_seq) - (derivative_yy_m_seq * delta_y)) / derivative_xy_m_seq
end # get_delta_x_seq

function delta_m_seq(derivative_x_m_seq::Float64, derivative_y_m_seq::Float64)
    return (derivative_x_m_seq^2 + derivative_y_m_seq^2)^Float64(0.5)
end # delta_m_seq

function calculate_delta_seq(kk::KamadaKawai, index::Int)
    derivative_x = derivative_x_m_seq(kk, index)
    derivative_y = derivative_y_m_seq(kk, index)

    return delta_m_seq(derivative_x, derivative_y)
end # calculate_delta_seq

function calculate_deltas_seq(kk::KamadaKawai)
    deltas = Vector{Float64}(undef, kk.n)

    for i in 1:kk.n
        deltas[i] = calculate_delta_seq(kk, i)
    end # for

    return deltas
end # calculate_deltas_seq

function get_max_delta_m_index_seq(deltas::Vector{Float64}, epsilon::Float64)
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
end # get_max_delta_m_index_seq

function seq(kk::KamadaKawai)
    states = Vector{Vector{Coord}}()
    # copy the coordinates into the first element of states
    push!(states, deepcopy(kk.coords))

    deltas = calculate_deltas_seq(kk)
    max_delta_m_seq_index = get_max_delta_m_index_seq(deltas, kk.epsilon)

    while max_delta_m_seq_index != -1
        while deltas[max_delta_m_seq_index] > kk.epsilon
            d_x_m = derivative_x_m_seq(kk, max_delta_m_seq_index)
            d_y_m = derivative_y_m_seq(kk, max_delta_m_seq_index)
            d_xx_m = derivative_xx_m_seq(kk, max_delta_m_seq_index)
            d_yy_m = derivative_yy_m_seq(kk, max_delta_m_seq_index)
            d_xy_m = derivative_xy_m_seq(kk, max_delta_m_seq_index)

            delta_y = get_delta_y_seq(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
            delta_x = get_delta_x_seq(d_y_m, d_yy_m, d_xy_m, delta_y)

            kk.coords[max_delta_m_seq_index].x += delta_x
            kk.coords[max_delta_m_seq_index].y += delta_y

            deltas[max_delta_m_seq_index] = calculate_delta_seq(kk, max_delta_m_seq_index)
        end # while
        
        deltas = calculate_deltas_seq(kk)
        max_delta_m_seq_index = get_max_delta_m_index_seq(deltas, kk.epsilon)
        
    end # while
    push!(states, deepcopy(kk.coords))

    return states
end # seq

end # module