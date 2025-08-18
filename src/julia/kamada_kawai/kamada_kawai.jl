module Kamada_Kawai

using Base.Threads
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

	addendx::Vector{Vector{Float64}}
	dx::Vector{Float64}
	addendy::Vector{Vector{Float64}}
	dy::Vector{Float64}

	deltas::Vector{Float64}

	K::Float64
	epsilon::Float64
	display::Float64
	limit::Int

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

	function KamadaKawai(coords::Vector{Any}, edges::Vector{Any}, K::Float64, epsilon::Float64, display::Float64, limit::Int)
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

		addendx = [zeros(Float64, n) for _ in 1:n]
		dx = zeros(Float64, n)
		addendy = [zeros(Float64, n) for _ in 1:n]
		dy = zeros(Float64, n)
		deltas = zeros(Float64, n)

		new(n, coords, m, edges, d_ij, l_ij, k_ij, addendx, dx, addendy, dy, deltas, K, epsilon, display, limit)
	end # KamadaKawai

end # Kamada_Kawai


export get_original_coords
export set_original_coords
export get_derivative_x!, get_derivative_y!
export get_delta_m_y, get_delta_m_x
export get_delta_m!
export get_deltas_seq!, get_deltas_par!
export update_deltas_seq!, update_deltas_par!
export get_derivatives_seq!, get_derivatives_par!
export get_addend_x, get_addend_y
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ####### FUNCTIONS  ####### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
function get_original_coords(kk::KamadaKawai, coords::Vector{Coord})
	kk.coords = deepcopy(coords)
end # get_original_coords
function set_original_coords(kk::KamadaKawai)
	coords = deepcopy(kk.coords)
end # set_original_coords
function get_delta_m_y(d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy)
	return (-d_m_xy * d_m_x + d_m_xx * d_m_y) / (-d_m_xx * d_m_yy + d_m_xy * d_m_xy)
end
function get_delta_m_x(d_m_y, d_m_yy, d_m_xy, delta_y)
	return (-d_m_y - d_m_yy * delta_y) / d_m_xy
end
function get_derivative_x!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendx[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_x - (kk.l_ij[index, i] * dist_x / sqrt(dist_x^2 + dist_y^2)))

		if !isnan(addend)
			kk.addendx[index][i] = addend
			sum += addend
		end
	end

	kk.dx[index] = sum
	return sum
end
function get_derivative_y!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendy[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_y - (kk.l_ij[index, i] * dist_y / sqrt(dist_x^2 + dist_y^2)))
		if !isnan(addend)
			kk.addendy[index][i] = addend
			sum += addend
		end
	end

	kk.dy[index] = sum
	return sum
end
function get_delta_m!(kk::KamadaKawai, index::Int)
	return sqrt(get_derivative_x!(kk, index)^2 + get_derivative_y!(kk, index)^2)
end
function get_addend_x(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index, m] * (dist_x - kk.l_ij[index, m] * dist_x / sqrt(dist_x^2 + dist_y^2))

	if isnan(addend)
		return 0
	end

	return addend
end
function get_addend_y(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index, m] * (dist_y - kk.l_ij[index, m] * dist_y / sqrt(dist_x^2 + dist_y^2))

	if isnan(addend)
		return 0
	end

	return addend
end

export update_delta_m!
function update_delta_m!(kk::KamadaKawai, m::Int, index::Int)
	tempx = get_addend_x(kk, m, index)
	tempy = get_addend_y(kk, m, index)

	kk.dx[index] = kk.dx[index] - kk.addendx[index][m] + tempx
	kk.dy[index] = kk.dy[index] - kk.addendy[index][m] + tempy

	kk.addendx[index][m] = tempx
	kk.addendy[index][m] = tempy

	return sqrt(kk.dx[index]^2 + kk.dy[index]^2)
end
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ### SEQUENTIAL VERSION ### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
function get_deltas_seq!(kk::KamadaKawai)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		kk.deltas[i] = get_delta_m!(kk, i)

		if kk.deltas[i] > kk.epsilon
			if kk.deltas[i] > max_delta
				max_delta = kk.deltas[i]
				delta_index = i
			end
		end
	end

	return delta_index
end
function update_deltas_seq!(kk::KamadaKawai, m::Int)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		if m == i
			continue
		end

		kk.deltas[i] = update_delta_m!(kk, m, i)

		if kk.deltas[i] > kk.epsilon && kk.deltas[i] > max_delta
			max_delta = kk.deltas[i]
			delta_index = i
		end
	end

	return delta_index
end
function get_derivatives_seq!(kk::KamadaKawai, index::Int)
	d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0

	for i in 1:kk.n
		if i == index
			continue
		end

		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		x2 = dist_x^2
		y2 = dist_y^2
		x2_y2 = x2 + y2
		x2_y2_1_2 = sqrt(x2_y2)
		x2_y2_3_2 = x2_y2^(1.5)

		addx  = kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / x2_y2_1_2));
		addy  = kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / x2_y2_1_2));
		addxx = kk.k_ij[index, i] * (1 - ((kk.l_ij[index, i] * y2) / x2_y2_3_2));
		addyy = kk.k_ij[index, i] * (1 - ((kk.l_ij[index, i] * x2) / x2_y2_3_2));
		addxy = kk.k_ij[index, i] * ((kk.l_ij[index, i] * dist_x * dist_y) / x2_y2_3_2);

		if !isnan(addx)
			d_m_x += addx
		end
		if !isnan(addy)
			d_m_y += addy
		end
		if !isnan(addxx)
			d_m_xx += addxx
		end
		if !isnan(addyy)
			d_m_yy += addyy
		end
		if !isnan(addxy)
			d_m_xy += addxy
		end
	end

	return d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy
end
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### #### PARALLEL VERSION #### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# function get_deltas_par!(kk::KamadaKawai)
# 	delta_index = -1
# 	max_delta = 0.0

# 	Threads.@threads :static for i in 1:kk.n
# 		kk.deltas[i] = get_delta_m!(kk, i)
# 	end

# 	for i in 1:kk.n
# 		if kk.deltas[i] > kk.epsilon && kk.deltas[i] > max_delta
# 			max_delta = kk.deltas[i]
# 			delta_index = i
# 		end
# 	end

# 	return delta_index
# end
# function update_deltas_par!(kk::KamadaKawai, m::Int)
#     n = kk.n
#     n_threads = nthreads()
    
#     # Parallel delta computation
#     @threads for i in 1:n
#         if m == i
#             continue
#         end
#         kk.deltas[i] = update_delta_m!(kk, m, i)
#     end
    
#     # Sequential reduction to find max (this part is inherently sequential)
#     delta_index = -1
#     max_delta = 0.0
    
#     for i in 1:n
#         if m == i
#             continue
#         end
        
#         if kk.deltas[i] > kk.epsilon && kk.deltas[i] > max_delta
#             max_delta = kk.deltas[i]
#             delta_index = i
#         end
#     end
    
#     return delta_index
# end
# function get_derivatives_par!(kk::KamadaKawai, index::Int)
#     d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0
    
#     coords_index = kk.coords[index]
    
#     @inbounds for i in 1:kk.n
#         if i == index
#             continue
#         end
        
#         # Cache array accesses
#         coords_i = kk.coords[i]
#         k_ij_val = kk.k_ij[index, i]
#         l_ij_val = kk.l_ij[index, i]

#         dist_x = coords_index.x - coords_i.x
#         dist_y = coords_index.y - coords_i.y

#         x2 = dist_x * dist_x  # Faster than ^2
#         y2 = dist_y * dist_y
#         x2_y2 = x2 + y2
        
#         # Avoid repeated sqrt and power calculations
#         x2_y2_sqrt = sqrt(x2_y2)
#         x2_y2_1_5 = x2_y2 * x2_y2_sqrt
        
#         l_over_sqrt = l_ij_val / x2_y2_sqrt
#         l_over_1_5 = l_ij_val / x2_y2_1_5

#         addx = k_ij_val * (dist_x - l_over_sqrt * dist_x)
#         addy = k_ij_val * (dist_y - l_over_sqrt * dist_y)
#         addxx = k_ij_val * (1 - l_over_1_5 * y2)
#         addyy = k_ij_val * (1 - l_over_1_5 * x2)
#         addxy = k_ij_val * (l_over_1_5 * dist_x * dist_y)

#         # Accumulate (NaN checks removed for speed - add back if needed)
#         d_m_x += addx
#         d_m_y += addy
#         d_m_xx += addxx
#         d_m_yy += addyy
#         d_m_xy += addxy
#     end

#     return d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy
# end
function get_deltas_par!(kk::KamadaKawai)
    n = kk.n
    n_threads = nthreads()
    
    # Only parallelize if worth it
    if n < 1000 || n_threads == 1
        return get_deltas_sequential!(kk)
    end
    
    chunk_size = cld(n, n_threads)  # Ceiling division
    
    # Parallel computation in chunks
    @threads for tid in 1:n_threads
        start_idx = (tid - 1) * chunk_size + 1
        end_idx = min(tid * chunk_size, n)
        
        # Each thread works on contiguous chunk (good cache locality)
        for i in start_idx:end_idx
            kk.deltas[i] = get_delta_m!(kk, i)
        end
    end
    
    # Sequential reduction (fast anyway)
    delta_index = -1
    max_delta = 0.0
    epsilon = kk.epsilon  # Cache field access
    
    @inbounds for i in 1:n
        delta_val = kk.deltas[i]
        if delta_val > epsilon && delta_val > max_delta
            max_delta = delta_val
            delta_index = i
        end
    end
    
    return delta_index
end

function update_deltas_par!(kk::KamadaKawai, m::Int)
    n = kk.n
    n_threads = nthreads()
    
    # Only parallelize if worth it
    if n < 1000 || n_threads == 1
        return update_deltas_sequential!(kk, m)
    end
    
    chunk_size = cld(n, n_threads)
    
    @threads for tid in 1:n_threads
        start_idx = (tid - 1) * chunk_size + 1
        end_idx = min(tid * chunk_size, n)
        
        for i in start_idx:end_idx
            if m == i
                continue
            end
            kk.deltas[i] = update_delta_m!(kk, m, i)
        end
    end
    
    # Sequential reduction
    delta_index = -1
    max_delta = 0.0
    epsilon = kk.epsilon
    
    @inbounds for i in 1:n
        if m == i
            continue
        end
        
        delta_val = kk.deltas[i]
        if delta_val > epsilon && delta_val > max_delta
            max_delta = delta_val
            delta_index = i
        end
    end
    
    return delta_index
end

function get_derivatives_par!(kk::KamadaKawai, index::Int)
    n = kk.n
    n_threads = nthreads()
    
    # This function is often not worth parallelizing - the work is O(n) but simple
    # Only try parallel for very large n
    if n < 5000 || n_threads == 1
        return get_derivatives_sequential!(kk, index)
    end
    
    chunk_size = cld(n, n_threads)
    thread_results = Vector{NTuple{5, Float64}}(undef, n_threads)
    
    @threads for tid in 1:n_threads
        start_idx = (tid - 1) * chunk_size + 1
        end_idx = min(tid * chunk_size, n)
        
        local_x = local_y = local_xx = local_yy = local_xy = 0.0
        coords_index = kk.coords[index]
        
        @inbounds for i in start_idx:end_idx
            if i == index
                continue
            end
            
            coords_i = kk.coords[i]
            k_ij_val = kk.k_ij[index, i]
            l_ij_val = kk.l_ij[index, i]

            dist_x = coords_index.x - coords_i.x
            dist_y = coords_index.y - coords_i.y

            x2 = dist_x * dist_x
            y2 = dist_y * dist_y
            x2_y2 = x2 + y2
            
            x2_y2_sqrt = sqrt(x2_y2)
            x2_y2_1_5 = x2_y2 * x2_y2_sqrt
            
            l_over_sqrt = l_ij_val / x2_y2_sqrt
            l_over_1_5 = l_ij_val / x2_y2_1_5

            local_x += k_ij_val * (dist_x - l_over_sqrt * dist_x)
            local_y += k_ij_val * (dist_y - l_over_sqrt * dist_y)
            local_xx += k_ij_val * (1 - l_over_1_5 * y2)
            local_yy += k_ij_val * (1 - l_over_1_5 * x2)
            local_xy += k_ij_val * (l_over_1_5 * dist_x * dist_y)
        end
        
        thread_results[tid] = (local_x, local_y, local_xx, local_yy, local_xy)
    end
    
    # Reduce results
    d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0
    for result in thread_results
        d_m_x += result[1]
        d_m_y += result[2]
        d_m_xx += result[3]
        d_m_yy += result[4]
        d_m_xy += result[5]
    end
    
    return d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy
end

# Sequential fallbacks (often faster for smaller problems)
function get_deltas_sequential!(kk::KamadaKawai)
    delta_index = -1
    max_delta = 0.0
    epsilon = kk.epsilon
    
    @inbounds for i in 1:kk.n
        delta_val = get_delta_m!(kk, i)
        kk.deltas[i] = delta_val
        
        if delta_val > epsilon && delta_val > max_delta
            max_delta = delta_val
            delta_index = i
        end
    end
    
    return delta_index
end

function update_deltas_sequential!(kk::KamadaKawai, m::Int)
    delta_index = -1
    max_delta = 0.0
    epsilon = kk.epsilon
    
    @inbounds for i in 1:kk.n
        if m == i
            continue
        end
        
        delta_val = update_delta_m!(kk, m, i)
        kk.deltas[i] = delta_val
        
        if delta_val > epsilon && delta_val > max_delta
            max_delta = delta_val
            delta_index = i
        end
    end
    
    return delta_index
end

function get_derivatives_sequential!(kk::KamadaKawai, index::Int)
    d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0
    coords_index = kk.coords[index]
    
    @inbounds for i in 1:kk.n
        if i == index
            continue
        end
        
        coords_i = kk.coords[i]
        k_ij_val = kk.k_ij[index, i]
        l_ij_val = kk.l_ij[index, i]

        dist_x = coords_index.x - coords_i.x
        dist_y = coords_index.y - coords_i.y

        x2 = dist_x * dist_x
        y2 = dist_y * dist_y
        x2_y2 = x2 + y2
        
        x2_y2_sqrt = sqrt(x2_y2)
        x2_y2_1_5 = x2_y2 * x2_y2_sqrt
        
        l_over_sqrt = l_ij_val / x2_y2_sqrt
        l_over_1_5 = l_ij_val / x2_y2_1_5

        d_m_x += k_ij_val * (dist_x - l_over_sqrt * dist_x)
        d_m_y += k_ij_val * (dist_y - l_over_sqrt * dist_y)
        d_m_xx += k_ij_val * (1 - l_over_1_5 * y2)
        d_m_yy += k_ij_val * (1 - l_over_1_5 * x2)
        d_m_xy += k_ij_val * (l_over_1_5 * dist_x * dist_y)
    end

    return d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy
end 

end #module