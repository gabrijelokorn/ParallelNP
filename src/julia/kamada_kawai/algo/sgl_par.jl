module Sgl_par
export sgl_par

using ...Kamada_Kawai

function sgl_par(kk::KamadaKawai)
	alltime = 0.0
	updatetime = 0.0
	start = Base.time_ns()
	delta_max_index = get_deltas_par!(kk);
	elapsed = Base.time_ns() - start
	println("elapsed get: ", elapsed / 1e9)

	while delta_max_index != -1
		steps = kk.limit

		while kk.deltas[delta_max_index] > kk.epsilon
			start = Base.time_ns()
			d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = get_derivatives_par!(kk, delta_max_index)
			elapsed = Base.time_ns() - start
			alltime += elapsed

			delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			delta_x = get_delta_m_x(d_y_m, d_yy_m, d_xy_m, delta_y)

			kk.coords[delta_max_index].x += delta_x
			kk.coords[delta_max_index].y += delta_y

			kk.deltas[delta_max_index] = get_delta_m!(kk, delta_max_index)

			steps -= 1
			if steps <= 0
				break
			end
		end # while

		startu = Base.time_ns()
		temp = update_deltas_par!(kk, delta_max_index);
		elapsedu = Base.time_ns() - startu
		updatetime += elapsedu

		if temp == delta_max_index
			break;
		end

		delta_max_index = temp;
	end # while

	println("get_derivatives_par!: ", alltime / 1e9)
	println("update_deltas_par!: ", updatetime / 1e9)
end # par

end # module