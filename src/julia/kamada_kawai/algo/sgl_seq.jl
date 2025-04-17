module Sgl_seq
export sgl_seq

using ...Kamada_Kawai

function sgl_seq(kk::KamadaKawai)
	delta_max_index = get_deltas_seq!(kk);

	while delta_max_index != -1
		steps = kk.limit

		while kk.deltas[delta_max_index] > kk.epsilon
			d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = get_derivatives_seq!(kk, delta_max_index)

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

		temp = update_deltas_seq!(kk, delta_max_index);
		if temp == delta_max_index
			break;
		end

		delta_max_index = temp;
	end # while
end # seq

end # module
