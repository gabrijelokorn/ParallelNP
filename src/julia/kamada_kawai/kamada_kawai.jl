module Kamada_Kawai

export Coord, Edge, KamadaKawai

mutable struct Coord 
    x::Float64
    y::Float64
end # Coord

mutable struct Edge
    Source::Int
    Target::Int
end # Edge

mutable struct KamadaKawai
    n::Int
    coords::Vector{Coord}
    m::Int
    edges::Vector{Edge}

    d_ij::Matrix{Int}
    l_ij::Matrix{Float64}
    k_ij::Matrix{Float64}

    K::Float64
    epsilon::Float64
    display::Float64

    function get_d_ij(n::Int, m::Int, edges::Vector{Edge})
        d_ij = fill(n + 1, n, n)
        for i in 1:n
            d_ij[i, i] = 0
        end

        for i in 1:m
            source = edges[i].Source
            target = edges[i].Target
            d_ij[source, target] = 1
            d_ij[target, source] = 1
        end

        # Floyd Warshall algorithm
        for k in 1:n
            for i in 1:n
                for j in 1:n
                    if d_ij[i, j] > d_ij[i, k] + d_ij[k, j]
                        d_ij[i, j] = d_ij[i, k] + d_ij[k, j]
                    end
                end
            end
        end

        return d_ij
    end # get_d_ij

    function get_l_ij(d_ij::Matrix{Int}, L::Float64)
        return d_ij .* L
    end # get_l_ij

    function get_k_ij(d_ij::Matrix{Int}, K::Float64)
        k_ij = K ./ (d_ij .^ 2)

        # Put 0 in the diagonal
        for i in 1:size(d_ij, 1)
            k_ij[i, i] = 0
        end

        return k_ij
    end # get_k_ij

    function KamadaKawai(coords::Vector{Any}, edges::Vector{Any}, K::Float64, epsilon::Float64, display::Float64)
        n = length(coords)
        m = length(edges)

        # Convert the coords to Coord
        coords = [Coord(coords[i]["x"], coords[i]["y"]) for i in 1:n]

        # Convert the edges to Edge
        edges = [Edge(edges[i]["source"], edges[i]["target"]) for i in 1:m]

        # Compute the d_ij matrix
        d_ij = get_d_ij(n, m, edges)

        # Get the max from d_ij
        max_d_ij = maximum(d_ij)

        # Compute the l_ij matrix
        L_0 = display
        L = L_0 / max_d_ij
        l_ij = get_l_ij(d_ij, L)

        # Compute the k_ij matrix
        k_ij = get_k_ij(d_ij, K)

        new(n, coords, m, edges, d_ij, l_ij, k_ij, K, epsilon, display)

    end # KamadaKawai

end # Kamada_Kawai

export derivative_x_m, derivative_y_m, derivative_xx_m,    derivative_yy_m,   derivative_xy_m

function derivative_x_m(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for
    
    return sum
end # derivative_x_m


function derivative_y_m(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / (dist_x^2 + dist_y^2)^(Float64(0.5))))
        end # if
    end # for
    
    return sum
end # derivative_y_m

function derivative_xx_m(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_y^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for
    
    return sum
end # derivative_xx_m

function derivative_yy_m(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (1 - (kk.l_ij[index, i] * dist_x^2) / (dist_x^2 + dist_y^2)^(Float64(1.5)))
        end # if
    end # for
    
    return sum
end # derivative_yy_m

function derivative_xy_m(kk::KamadaKawai, index::Int)
    sum = 0.0
    for i in 1:kk.n
        if i != index
            dist_x = kk.coords[index].x - kk.coords[i].x
            dist_y = kk.coords[index].y - kk.coords[i].y

            sum += kk.k_ij[index, i] * (kk.l_ij[index, i] * dist_x * dist_y) / (dist_x^2 + dist_y^2)^(Float64(1.5))
        end # if
    end # for
    
    return sum
end # derivative_xy_m

end # module