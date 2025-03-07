package algo

import (
	"math"
	"sync"
)

func derivative_x_m_par(kk *KamadaKawai, index int) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == index {
			continue
		}

		var dist_x float64 = kk.Coords[index].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[index].Y - kk.Coords[i].Y

		sum += kk.K_ij[index][i] * (dist_x - ((kk.L_ij[index][i] * dist_x) / (math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(1)/float64(2)))))
	}

	return sum
}

func derivative_y_m_par(kk *KamadaKawai, index int) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == index {
			continue
		}

		var dist_x float64 = kk.Coords[index].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[index].Y - kk.Coords[i].Y

		sum += kk.K_ij[index][i] * (dist_y - ((kk.L_ij[index][i] * dist_y) / (math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(1)/float64(2)))))
	}

	return sum
}

func derivative_xx_m_par(kk *KamadaKawai, index int) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == index {
			continue
		}

		var dist_x float64 = kk.Coords[index].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[index].Y - kk.Coords[i].Y

		sum += kk.K_ij[index][i] * (1 - ((kk.L_ij[index][i] * math.Pow(dist_y, 2)) / math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(3)/float64(2))))
	}

	return sum
}

func derivative_yy_m_par(kk *KamadaKawai, index int) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == index {
			continue
		}

		var dist_x float64 = kk.Coords[index].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[index].Y - kk.Coords[i].Y

		sum += kk.K_ij[index][i] * (1 - ((kk.L_ij[index][i] * math.Pow(dist_x, 2)) / math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(3)/float64(2))))
	}

	return sum
}

func derivative_xy_m_par(kk *KamadaKawai, index int) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == index {
			continue
		}

		var dist_x float64 = kk.Coords[index].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[index].Y - kk.Coords[i].Y

		sum += kk.K_ij[index][i] * ((kk.L_ij[index][i] * dist_x * dist_y) / math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(3)/float64(2)))
	}

	return sum
}

func get_delta_x_par_par(
	derivative_x_m_par float64,
	derivative_y_m_par float64,
	derivative_xx_m_par float64,
	derivative_yy_m_par float64,
	derivative_xy_m_par float64) float64 {
	return (-(derivative_xy_m_par * derivative_x_m_par) + (derivative_xx_m_par * derivative_y_m_par)) / (-(derivative_xx_m_par * derivative_yy_m_par) + (derivative_xy_m_par * derivative_xy_m_par))
}

func get_delta_x(
	derivative_y_m_par float64,
	derivative_yy_m_par float64,
	derivative_xy_m_par float64,
	delta_y float64) float64 {
	return (-(derivative_y_m_par) - (derivative_yy_m_par * delta_y)) / (derivative_xy_m_par)
}

func delta_m(derivative_x float64, derivative_y float64) float64 {
	return math.Sqrt(math.Pow(derivative_x, 2) + math.Pow(derivative_y, 2))
}

func calculate_delta_par(kk *KamadaKawai, index int) float64 {
	derivative_x := derivative_x_m_par(kk, index)
	derivative_y := derivative_y_m_par(kk, index)

	return delta_m(derivative_x, derivative_y)
}

func calculate_deltas_par(kk *KamadaKawai) []float64 {
	var deltas []float64 = make([]float64, kk.N)

	wg := sync.WaitGroup{}
	for i := 0; i < kk.N; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			deltas[i] = calculate_delta_par(kk, i)
		}(i)
	}
	wg.Wait()

	return deltas
}

func get_max_delta_m_index_par(deltas []float64, epsilon float64) int {
	var max float64 = -1
	var index int = -1

	for i, delta := range deltas {
		if delta > max {
			max = delta
			if delta > epsilon {
				index = i
			}
		}
	}

	return index
}

func (kk *KamadaKawai) Par() [][]Coord {
	states := make([][]Coord, 1)
	states[0] = make([]Coord, kk.N)
	copy(states[0], kk.Coords)

	var deltas []float64 = calculate_deltas_par(kk)
	var max_delta_m_index int = get_max_delta_m_index_par(deltas, kk.Epsilon)

	for {
		if max_delta_m_index == -1 {
			break
		}

		for {
			var (
				d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m float64
			)

			wg := sync.WaitGroup{}
			wg.Add(5)

			go func() {
				defer wg.Done()
				d_x_m = derivative_x_m_par(kk, max_delta_m_index)
			}()
			go func() {
				defer wg.Done()
				d_y_m = derivative_y_m_par(kk, max_delta_m_index)
			}()
			go func() {
				defer wg.Done()
				d_xx_m = derivative_xx_m_par(kk, max_delta_m_index)
			}()
			go func() {
				defer wg.Done()
				d_yy_m = derivative_yy_m_par(kk, max_delta_m_index)
			}()
			go func() {
				defer wg.Done()
				d_xy_m = derivative_xy_m_par(kk, max_delta_m_index)
			}()
			wg.Wait()

			var delta_y float64 = get_delta_x_par_par(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			var delta_x float64 = get_delta_x(d_y_m, d_yy_m, d_xy_m, delta_y)

			kk.Coords[max_delta_m_index].X += delta_x
			kk.Coords[max_delta_m_index].Y += delta_y

			deltas[max_delta_m_index] = calculate_delta_par(kk, max_delta_m_index)
			if deltas[max_delta_m_index] < kk.Epsilon {
				break
			}
		}

		deltas = calculate_deltas_par(kk)
		max_delta_m_index = get_max_delta_m_index_par(deltas, kk.Epsilon)
	}
	state := make([]Coord, kk.N)
	copy(state, kk.Coords)
	states = append(states, state)

	return states
}
