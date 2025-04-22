module Mlt_seq
export mlt_seq

using ...Kamada_Kawai

function mlt_seq(kk::KamadaKawai)
	steps = kk.limit

	while true
		equilibrium::Bool = true;

		for i in 1:kk.n
			d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = get_derivatives_seq!(kk, i)

			delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			delta_x = get_delta_m_x(d_y_m, d_yy_m, d_xy_m, delta_y)

			kk.coords[i].x += delta_x
			kk.coords[i].y += delta_y

			kk.deltas[i] = get_delta_m!(kk, i)
		end

		for i in 1:kk.n
			if kk.deltas[i] > kk.epsilon
				equilibrium = false
			end
		end

		if equilibrium
			break
		end

		steps -= 1
		if steps <= 0
			break
		end
	end # while

end # mlt_seq

end # module
