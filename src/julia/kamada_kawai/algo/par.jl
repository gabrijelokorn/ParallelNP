module Par
export Par

using ...Kamada_Kawai

function par(kk::KamadaKawai)
	delta_max_index = @inbounds get_deltas_par!(kk);

	while delta_max_index != -1
		steps = kk.limit

		while kk.deltas[delta_max_index] > kk.epsilon
			d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = @inbounds get_derivatives_par!(kk, delta_max_index)
			
			delta_y = @inbounds get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			delta_x = @inbounds get_delta_m_x(d_y_m, d_yy_m, d_xy_m, delta_y)
			
			kk.coords[delta_max_index].x += delta_x
			kk.coords[delta_max_index].y += delta_y
			
			kk.deltas[delta_max_index] = @inbounds get_delta_m_par!(kk, delta_max_index)
			
			steps -= 1
			if steps <= 0
				break
			end
		end # while

		temp = @inbounds update_deltas_par!(kk);

		if temp == delta_max_index
			break;
		end

		delta_max_index = temp;
	end # while

end # par

end # module