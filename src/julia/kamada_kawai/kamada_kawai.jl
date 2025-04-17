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
function get_original_coords(kk::KamadaKawai, coords::Vector{Coord})
	kk.coords = deepcopy(coords)
end # get_original_coords

export set_original_coords
function set_original_coords(kk::KamadaKawai)
	coords = deepcopy(kk.coords)
end # set_original_coords

export get_delta_m_y, get_delta_m_x
function get_delta_m_y(d_m_x, d_m_y, d_m_xx, d_m_yy, d_m_xy)
	return (-d_m_xy * d_m_x + d_m_xx * d_m_y) / (-d_m_xx * d_m_yy + d_m_xy * d_m_xy)
end
function get_delta_m_x(d_m_y, d_m_yy, d_m_xy, delta_y)
	return (-d_m_y - d_m_yy * delta_y) / d_m_xy
end

export get_derivative_x!,get_derivative_y!
function get_derivative_x!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendx[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y
		
		addend = kk.k_ij[index,i] * (dist_x - (kk.l_ij[index,i] * dist_x / sqrt(dist_x^2 + dist_y^2)))

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

		addend = kk.k_ij[index,i] * (dist_y - (kk.l_ij[index,i] * dist_y / sqrt(dist_x^2 + dist_y^2)))
		if !isnan(addend)
			kk.addendy[index][i] = addend
			sum += addend
		end
	end

	kk.dy[index] = sum
	return sum
end

export get_delta_m!
function get_delta_m!(kk::KamadaKawai, index::Int)
	return sqrt(get_derivative_x!(kk, index)^2 + get_derivative_y!(kk, index)^2)
end

export get_deltas_seq!, get_deltas_par!
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
function get_deltas_par!(kk::KamadaKawai)
    # Parallel computation of deltas
    Threads.@threads for i in 1:kk.n
        kk.deltas[i] = get_delta_m!(kk, i)
    end

    # Find max delta and index (single-threaded)
    delta_index = -1
    max_delta = 0.0
    for i in 1:kk.n
        if kk.deltas[i] > kk.epsilon && kk.deltas[i] > max_delta
            max_delta = kk.deltas[i]
            delta_index = i
        end
    end

    return delta_index
end


export get_addend_x,get_addend_y
function get_addend_x(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index,m] * (dist_x - kk.l_ij[index,m] * dist_x / sqrt(dist_x^2 + dist_y^2))

	if isnan(addend)
		return 0
	end

	return addend
end
function get_addend_y(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index,m] * (dist_y - kk.l_ij[index,m] * dist_y / sqrt(dist_x^2 + dist_y^2))

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

export update_deltas_seq!, update_deltas_par!
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
function update_deltas_par!(kk::KamadaKawai, m::Int)
    n = kk.n
    nthreads = Threads.nthreads()
    
    # Thread-local storage for max delta tracking
    max_deltas = fill((0.0, -1), nthreads)
    
    Threads.@threads for i in 1:n
        if i != m
            delta = update_delta_m!(kk, m, i)
            kk.deltas[i] = delta
            
            # Track thread-local max
            tid = Threads.threadid()
            if delta > kk.epsilon && delta > max_deltas[tid][1]
                max_deltas[tid] = (delta, i)
            end
        end
    end
    
    # Find global max (parallel reduction)
    max_delta = 0.0
    delta_index = -1
    for (d, idx) in max_deltas
        if d > max_delta
            max_delta = d
            delta_index = idx
        end
    end
    
    return delta_index
end


export get_derivatives_seq!, get_derivatives_par!
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

		addx  = kk.k_ij[index,i] * (dist_x - ((kk.l_ij[index,i] * dist_x) / x2_y2_1_2));
		addy  = kk.k_ij[index,i] * (dist_y - ((kk.l_ij[index,i] * dist_y) / x2_y2_1_2));
		addxx = kk.k_ij[index,i] * (1 - ((kk.l_ij[index,i] * y2) / x2_y2_3_2));
		addyy = kk.k_ij[index,i] * (1 - ((kk.l_ij[index,i] * x2) / x2_y2_3_2));
		addxy = kk.k_ij[index,i] * ((kk.l_ij[index,i] * dist_x * dist_y) / x2_y2_3_2);

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
struct ThreadAccums
	x::Float64
	y::Float64
	xx::Float64
	yy::Float64
	xy::Float64
end
function get_derivatives_par!(kk::KamadaKawai, index::Int)
    # Use a struct to avoid false sharing

    nthreads = Threads.nthreads()
    accumulators = [ThreadAccums(0.0, 0.0, 0.0, 0.0, 0.0) for _ in 1:nthreads]

    Threads.@threads :static for i in 1:kk.n
        i == index && continue
        
        tid = Threads.threadid()
        acc = accumulators[tid]
        
        dist_x = kk.coords[index].x - kk.coords[i].x
        dist_y = kk.coords[index].y - kk.coords[i].y

        x2 = dist_x^2
        y2 = dist_y^2
        x2_y2 = x2 + y2
        x2_y2_1_2 = sqrt(x2_y2)
        x2_y2_3_2 = x2_y2 * x2_y2_1_2  # More efficient than ^1.5

        kij = kk.k_ij[index, i]
        lij = kk.l_ij[index, i]

        inv_dist = lij / x2_y2_1_2
        inv_dist3 = lij / x2_y2_3_2

        # Calculate all terms
        addx = kij * (dist_x - dist_x * inv_dist)
        addy = kij * (dist_y - dist_y * inv_dist)
        addxx = kij * (1.0 - y2 * inv_dist3)
        addyy = kij * (1.0 - x2 * inv_dist3)
        addxy = kij * (dist_x * dist_y * inv_dist3)

        # Accumulate (NaN checks are expensive, only use if absolutely necessary)
        acc = ThreadAccums(
            acc.x + ifelse(isnan(addx), 0.0, addx),
            acc.y + ifelse(isnan(addy), 0.0, addy),
            acc.xx + ifelse(isnan(addxx), 0.0, addxx),
            acc.yy + ifelse(isnan(addyy), 0.0, addyy),
            acc.xy + ifelse(isnan(addxy), 0.0, addxy)
        )
        accumulators[tid] = acc
    end

    # Reduction
    return (
        sum(a.x for a in accumulators),
        sum(a.y for a in accumulators),
        sum(a.xx for a in accumulators),
        sum(a.yy for a in accumulators),
        sum(a.xy for a in accumulators)
    )
end

end #module
