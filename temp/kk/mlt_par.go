package algo

import "sync"

func (kk *KamadaKawai) Mlt_par() {
	var steps int64 = kk.Limit

	for {
		var equilibrium = true

		var wg sync.WaitGroup

		for i := 0; i < kk.N; i++ {
			wg.Add(1)

			go func(i int) {
				defer wg.Done()
				d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m := kk.get_derivatives_par(int64(i))

				var delta_y float64 = kk.get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
				var delta_x float64 = kk.get_delta_m_x(d_y_m, d_yy_m, d_xy_m, delta_y)

				kk.mu.Lock()
				kk.Coords[i].X += delta_x
				kk.Coords[i].Y += delta_y
				kk.Deltas[i] = kk.get_delta_m(int64(i))
				kk.mu.Unlock()
			}(i)
		}
		wg.Wait()

		for i := 0; i < kk.N; i++ {
			if kk.Deltas[i] > kk.Epsilon {
				equilibrium = false
			}
		}

		if equilibrium {
			break
		}
		steps--
		if steps <= 0 {
			break
		}
	}
}
