package algo

import (
	"math"
)

func get_delta_y_seq(
	derivative_x_m float64,
	derivative_y_m float64,
	derivative_xx_m float64,
	derivative_yy_m float64,
	derivative_xy_m float64) float64 {
	return (-(derivative_xy_m * derivative_x_m) + (derivative_xx_m * derivative_y_m)) / (-(derivative_xx_m * derivative_yy_m) + (derivative_xy_m * derivative_xy_m))
}

func get_delta_x_seq(
	derivative_y_m float64,
	derivative_yy_m float64,
	derivative_xy_m float64,
	delta_y float64) float64 {
	return (-(derivative_y_m) - (derivative_yy_m * delta_y)) / (derivative_xy_m)
}

func delta_m_seq(derivative_x float64, derivative_y float64) float64 {
	return math.Sqrt(math.Pow(derivative_x, 2) + math.Pow(derivative_y, 2))
}

func calculate_delta_seq(kk *KamadaKawai, index int) float64 {
	derivative_x := kk.derivative_x_m(index)
	derivative_y := kk.derivative_y_m(index)

	return delta_m_seq(derivative_x, derivative_y)
}

func calculate_deltas_seq(kk *KamadaKawai) []float64 {
	var deltas []float64 = make([]float64, kk.N)

	for i := 0; i < kk.N; i++ {
		deltas[i] = calculate_delta_seq(kk, i)
	}

	return deltas
}

func get_max_delta_m_index_seq(deltas []float64, epsilon float64) int {
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

func (kk *KamadaKawai) Seq() [][]Coord {

	states := make([][]Coord, 1)
	states[0] = make([]Coord, kk.N)
	copy(states[0], kk.Coords)

	var deltas []float64 = calculate_deltas_seq(kk)
	var max_delta_m_seq_index int = get_max_delta_m_index_seq(deltas, kk.Epsilon)

	for {
		if max_delta_m_seq_index == -1 {
			break
		}

		for {
			var d_x_m = kk.derivative_x_m(max_delta_m_seq_index)
			var d_y_m = kk.derivative_y_m(max_delta_m_seq_index)
			var d_xx_m = kk.derivative_xx_m(max_delta_m_seq_index)
			var d_yy_m = kk.derivative_yy_m(max_delta_m_seq_index)
			var d_xy_m = kk.derivative_xy_m(max_delta_m_seq_index)

			var delta_y float64 = get_delta_y_seq(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m)
			var delta_x float64 = get_delta_x_seq(d_y_m, d_yy_m, d_xy_m, delta_y)

			kk.Coords[max_delta_m_seq_index].X += delta_x
			kk.Coords[max_delta_m_seq_index].Y += delta_y

			deltas[max_delta_m_seq_index] = calculate_delta_seq(kk, max_delta_m_seq_index)
			if deltas[max_delta_m_seq_index] < kk.Epsilon {
				break
			}
		}

		deltas = calculate_deltas_seq(kk)
		max_delta_m_seq_index = get_max_delta_m_index_seq(deltas, kk.Epsilon)
	}
	state := make([]Coord, kk.N)
	copy(state, kk.Coords)
	states = append(states, state)

	return states
}
