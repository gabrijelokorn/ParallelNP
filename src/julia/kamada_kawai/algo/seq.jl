module Seq
export seq

using ...Kamada_Kawai

function get_delta_y_seq(
    derivative_x_m::Float64,
    derivative_y_m::Float64,
    derivative_xx_m::Float64,
    derivative_yy_m::Float64,
    derivative_xy_m::Float64
)
    return (-(derivative_xy_m * derivative_x_m) + (derivative_xx_m * derivative_y_m)) / (-(derivative_xx_m * derivative_yy_m) + derivative_xy_m^2)
end # get_delta_y_seq

function get_delta_x_seq(
    derivative_y_m::Float64,
    derivative_yy_m::Float64,
    derivative_xy_m::Float64,
    delta_y::Float64
)
    return (-(derivative_y_m) - (derivative_yy_m * delta_y)) / derivative_xy_m
end # get_delta_x_seq

function delta_m_seq(derivative_x_m::Float64, derivative_y_m::Float64)
    return (derivative_x_m^2 + derivative_y_m^2)^Float64(0.5)
end # delta_m_seq

function calculate_delta_seq(kk::KamadaKawai, index::Int)
    derivative_x = derivative_x_m(kk, index)
    derivative_y = derivative_y_m(kk, index)

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
            d_x_m = derivative_x_m(kk, max_delta_m_seq_index)
            d_y_m = derivative_y_m(kk, max_delta_m_seq_index)
            d_xx_m = derivative_xx_m(kk, max_delta_m_seq_index)
            d_yy_m = derivative_yy_m(kk, max_delta_m_seq_index)
            d_xy_m = derivative_xy_m(kk, max_delta_m_seq_index)

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