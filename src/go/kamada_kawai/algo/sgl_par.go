package algo

func (kk *KamadaKawai) Sgl_par() {
	var delta_max_index int64 = kk.get_deltas_par()

	for {
		if delta_max_index == -1 {
			break
		}
		var steps int64 = kk.Limit

		for {
			if kk.Deltas[delta_max_index] < kk.Epsilon {
				break
			}

			d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m := kk.get_derivatives_par(delta_max_index)
			var delta_y float64 = kk.get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			var delta_x float64 = kk.get_delta_m_x(d_y_m, d_yy_m, d_xy_m, delta_y)
			kk.Coords[delta_max_index].X += delta_x
			kk.Coords[delta_max_index].Y += delta_y

			kk.Deltas[delta_max_index] = kk.get_delta_m_par(delta_max_index)

			steps--
			if steps <= 0 {
				break
			}
		}
		var temp int64 = kk.update_deltas_par(delta_max_index)
		if temp == delta_max_index {
			break
		}
		delta_max_index = temp
	}
}
