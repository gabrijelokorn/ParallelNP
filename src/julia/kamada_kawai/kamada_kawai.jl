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


# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ####### FUNCTIONS  ####### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
export get_original_coords
export set_original_coords
export get_delta_m_y, get_delta_m_x
export get_addend_x, get_addend_y
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
function get_addend_x(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index, m] * (dist_x - kk.l_ij[index, m] * dist_x / sqrt(dist_x * dist_x + dist_y * dist_y))

	if isnan(addend)
		return 0
	end

	return addend
end
function get_addend_y(kk::KamadaKawai, m::Int, index::Int)
	dist_x = kk.coords[index].x - kk.coords[m].x
	dist_y = kk.coords[index].y - kk.coords[m].y

	addend = kk.k_ij[index, m] * (dist_y - kk.l_ij[index, m] * dist_y / sqrt(dist_x * dist_x + dist_y * dist_y))

	if isnan(addend)
		return 0
	end

	return addend
end

export update_delta_m_mem!
function update_delta_m_mem!(kk::KamadaKawai, m::Int, index::Int)
	tempx = get_addend_x(kk, m, index)
	tempy = get_addend_y(kk, m, index)

	kk.dx[index] = kk.dx[index] - kk.addendx[index][m] + tempx
	kk.dy[index] = kk.dy[index] - kk.addendy[index][m] + tempy

	kk.addendx[index][m] = tempx
	kk.addendy[index][m] = tempy

	return sqrt(kk.dx[index] * kk.dx[index] + kk.dy[index] * kk.dy[index])
end
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ### NON-MERMORY VERSION ### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
export update_delta_m!
function update_delta_m!(kk::KamadaKawai, index::Int)
	dx = 0.0
	dy = 0.0

	for i in 1:kk.n
		dx += @inbounds get_addend_x(kk, i, index)
		dy += @inbounds get_addend_y(kk, i, index)
	end

	return sqrt(dx * dx + dy * dy)
end

# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ### SEQUENTIAL VERSION ### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
export get_deltas_mem_seq!
export update_deltas_mem_seq!
export get_derivatives_mem_seq!
export get_derivative_x_mem_seq!, get_derivative_y_mem_seq!
export get_delta_m_mem_seq!
function get_derivative_x_mem_seq!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendx[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_x - (kk.l_ij[index, i] * dist_x / sqrt(dist_x * dist_x + dist_y * dist_y)))

		if !isnan(addend)
			kk.addendx[index][i] = addend
			sum += addend
		end
	end

	kk.dx[index] = sum
	return sum
end
function get_derivative_y_mem_seq!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendy[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_y - (kk.l_ij[index, i] * dist_y / sqrt(dist_x * dist_x + dist_y * dist_y)))
		if !isnan(addend)
			kk.addendy[index][i] = addend
			sum += addend
		end
	end

	kk.dy[index] = sum
	return sum
end
function get_delta_m_mem_seq!(kk::KamadaKawai, index::Int)
	dx = get_derivative_x_mem_seq!(kk, index)
	dy = get_derivative_y_mem_seq!(kk, index)
	return sqrt(dx * dx + dy * dy)
end
function get_deltas_mem_seq!(kk::KamadaKawai)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		kk.deltas[i] = get_delta_m_mem_seq!(kk, i)

		if kk.deltas[i] > kk.epsilon
			if kk.deltas[i] > max_delta
				max_delta = kk.deltas[i]
				delta_index = i
			end
		end
	end

	return delta_index
end
function update_deltas_mem_seq!(kk::KamadaKawai, m::Int)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		if m == i
			continue
		end

		kk.deltas[i] = update_delta_m_mem!(kk, m, i)

		if kk.deltas[i] > kk.epsilon && kk.deltas[i] > max_delta
			max_delta = kk.deltas[i]
			delta_index = i
		end
	end

	return delta_index
end
function get_derivatives_mem_seq!(kk::KamadaKawai, index::Int)
	d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0

	for i in 1:kk.n
		if i == index
			continue
		end

		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		x2 = dist_x * dist_x
		y2 = dist_y * dist_y
		x2_y2 = x2 + y2
		x2_y2_1_2 = sqrt(x2_y2)
		x2_y2_3_2 = x2_y2 * sqrt(x2_y2)

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
export get_deltas_mem_par!
export update_deltas_mem_par!
export get_derivatives_mem_par!
export get_derivative_x_mem_par!, get_derivative_y_mem_par!
export get_delta_m_mem_par!
function get_derivative_x_mem_par!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendx[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_x - (kk.l_ij[index, i] * dist_x / sqrt(dist_x * dist_x + dist_y * dist_y)))

		if !isnan(addend)
			kk.addendx[index][i] = addend
			sum += addend
		end
	end

	kk.dx[index] = sum
	return sum
end

function get_derivative_y_mem_par!(kk::KamadaKawai, index::Int)
	sum = 0.0
	for i in 1:kk.n
		if i == index
			kk.addendy[index][i] = 0.0
			continue
		end
		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		addend = kk.k_ij[index, i] * (dist_y - (kk.l_ij[index, i] * dist_y / sqrt(dist_x * dist_x + dist_y * dist_y)))
		if !isnan(addend)
			kk.addendy[index][i] = addend
			sum += addend
		end
	end

	kk.dy[index] = sum
	return sum
end

function get_delta_m_mem_par!(kk::KamadaKawai, index::Int)
	dx = get_derivative_x_mem_par!(kk, index)
	dy = get_derivative_y_mem_par!(kk, index)
	return sqrt(dx * dx + dy * dy)
end

function get_deltas_mem_par!(kk::KamadaKawai)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		kk.deltas[i] = get_delta_m_mem_seq!(kk, i)

		if kk.deltas[i] > kk.epsilon
			if kk.deltas[i] > max_delta
				max_delta = kk.deltas[i]
				delta_index = i
			end
		end
	end

	return delta_index
end

function update_deltas_mem_par!(kk::KamadaKawai, m::Int)
	nt = nthreads()
	local_max = fill(-Inf, nt)
	local_idx = fill(-1, nt)

	@threads for i in 1:kk.n
		if i == m
			continue
		end

		delta = update_delta_m_mem!(kk, m, i)
		kk.deltas[i] = delta

		tid = threadid()
		if delta > kk.epsilon && delta > local_max[tid]
			local_max[tid] = delta
			local_idx[tid] = i
		end
	end

	max_delta = 0.0
	delta_index = -1
	for t in 1:nt
		if local_max[t] > max_delta
			max_delta = local_max[t]
			delta_index = local_idx[t]
		end
	end
	return delta_index
end

function get_derivatives_mem_par!(kk::KamadaKawai, index::Int)
	d_m_x = d_m_y = d_m_xx = d_m_yy = d_m_xy = 0.0

	for i in 1:kk.n
		if i == index
			continue
		end

		dist_x = kk.coords[index].x - kk.coords[i].x
		dist_y = kk.coords[index].y - kk.coords[i].y

		x2 = dist_x * dist_x
		y2 = dist_y * dist_y
		x2_y2 = x2 + y2
		x2_y2_1_2 = sqrt(x2_y2)
		x2_y2_3_2 = x2_y2 * sqrt(x2_y2)

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
# // ### ### ### #### NON-MEMORY PARALLEL VERSION #### ### ### ### //
# // ### ### ### ########################## ### ### ### //
# // ### ### ### ########################## ### ### ### //
export get_deltas_par!
export update_deltas_par!
export get_derivatives_par!
export get_derivative_x_par!, get_derivative_y_par!
export get_delta_m_par!
function get_derivative_x_par!(kk::KamadaKawai, index::Int)
	sum = 0.0

	for i in 1:kk.n
		if i != index
			dist_x = kk.coords[index].x - kk.coords[i].x
			dist_y = kk.coords[index].y - kk.coords[i].y

			addend = kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / sqrt(dist_x*dist_x + dist_y*dist_y)))

			if !isnan(addend)
				sum += addend
			end
		end
	end

	return sum
end


function get_derivative_y_par!(kk::KamadaKawai, index::Int)
	sum = 0.0

	for i in 1:kk.n
		if i != index
			dist_x = kk.coords[index].x - kk.coords[i].x
			dist_y = kk.coords[index].y - kk.coords[i].y

			addend = kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / sqrt(dist_x*dist_x + dist_y*dist_y)))

			if !isnan(addend)
				sum += addend
			end
		end
	end

	return sum
end


function get_delta_m_par!(kk::KamadaKawai, index::Int)
	dx = get_derivative_x_par!(kk, index)
	dy = get_derivative_y_par!(kk, index)
	return sqrt(dx * dx + dy * dy)
end


function get_deltas_par!(kk::KamadaKawai)
	delta_index = -1
	max_delta = 0.0

	for i in 1:kk.n
		kk.deltas[i] = get_delta_m_par!(kk, i)

		if kk.deltas[i] > kk.epsilon
			if kk.deltas[i] > max_delta
				max_delta = kk.deltas[i]
				delta_index = i
			end
		end
	end

	return delta_index
end
function update_deltas_par!(kk::KamadaKawai)
	delta_index = -1
	max_delta = 0.0

	Threads.@threads :static for i in 1:kk.n
		@inbounds kk.deltas[i] = update_delta_m!(kk, i)
	end

	for i in 1:kk.n
		if kk.deltas[i] > kk.epsilon
			if kk.deltas[i] > max_delta
				max_delta = kk.deltas[i]
				delta_index = i
			end
		end
	end

	return delta_index
end
function get_derivatives_par!(kk::KamadaKawai, index::Int)
	d_x_m  = 0.0
	d_y_m  = 0.0
	d_xx_m = 0.0
	d_yy_m = 0.0
	d_xy_m = 0.0

	for i in 1:kk.n
		if i != index
			dist_x = kk.coords[index].x - kk.coords[i].x
			dist_y = kk.coords[index].y - kk.coords[i].y

			x2 = dist_x * dist_x
			y2 = dist_y * dist_y
			x2_y2 = x2 + y2
			x2_y2_1_2 = sqrt(x2_y2)
			x2_y2_3_2 = x2_y2 * sqrt(x2_y2)

			addx  = kk.k_ij[index, i] * (dist_x - ((kk.l_ij[index, i] * dist_x) / x2_y2_1_2));
			addy  = kk.k_ij[index, i] * (dist_y - ((kk.l_ij[index, i] * dist_y) / x2_y2_1_2));
			addxx = kk.k_ij[index, i] * (1 - ((kk.l_ij[index, i] * y2) / x2_y2_3_2));
			addyy = kk.k_ij[index, i] * (1 - ((kk.l_ij[index, i] * x2) / x2_y2_3_2));
			addxy = kk.k_ij[index, i] * ((kk.l_ij[index, i] * dist_x * dist_y) / x2_y2_3_2);

			if !isnan(addx)
				d_x_m += addx
			end
			if !isnan(addy)
				d_y_m += addy
			end
			if !isnan(addxx)
				d_xx_m += addxx
			end
			if !isnan(addyy)
				d_yy_m += addyy
			end
			if !isnan(addxy)
				d_xy_m += addxy
			end
		end
	end

	return d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m
end

end
