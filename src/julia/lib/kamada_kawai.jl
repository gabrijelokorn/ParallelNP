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

    function get_d_ij(n::Int, coords::Vector{Coord}, m::Int, edges::Vector{Edge})
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

    function KamadaKawai(coords::Vector{Any}, edges::Vector{Any}, K::Float64, epsilon::Float64, display::Float64)
        n = length(coords)
        m = length(edges)

        # Convert the coords to Coord
        coords = [Coord(coords[i]["x"], coords[i]["y"]) for i in 1:n]

        # Convert the edges to Edge
        edges = [Edge(edges[i]["source"], edges[i]["target"]) for i in 1:m]

        # Compute the d_ij matrix
        d_ij = get_d_ij(n, coords, m, edges)

        # Get the max from d_ij
        max_d_ij = maximum(d_ij)

        # Compute the l_ij matrix
        L_0 = display
        L = L_0 / max_d_ij
        l_ij = d_ij .* L

        # Compute the k_ij matrix
        k_ij = K ./ (d_ij .^ 2)

        new(n, coords, m, edges, d_ij, l_ij, k_ij, K, epsilon, display)
    end # KamadaKawai

end # Kamada_Kawai
end # module