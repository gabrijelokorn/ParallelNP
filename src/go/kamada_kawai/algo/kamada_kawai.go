package algo

import (
	"math"
	"sync"
)

// ############# KAMADA KAWAI DATA STRUCTURE ############# //

type Coord struct {
	X float64 `json:"x"`
	Y float64 `json:"y"`
}

type Edge struct {
	Source int `json:"source"`
	Target int `json:"target"`
}

type KamadaKawai struct {
	N      int
	Coords []Coord `json:"coords"`

	M    int
	Edge []Edge `json:"edges"`

	D_ij [][]int
	L_ij [][]float64
	K_ij [][]float64

	Addendx [][]float64
	Dx      []float64
	Addendy [][]float64
	Dy      []float64

	Deltas []float64

	K       float64 `json:"K"`
	Epsilon float64 `json:"epsilon"`
	Display float64 `json:"display"`
	Limit   int64   `json:"limit"`

	mu sync.RWMutex
}

func (kk *KamadaKawai) Init() {
	// Initialize N and M
	kk.N = len(kk.Coords)
	kk.M = len(kk.Edge)

	// Initialize D_ij
	kk.D_ij = make([][]int, kk.N)
	for i := 0; i < kk.N; i++ {
		kk.D_ij[i] = make([]int, kk.N)
	}
	for i := 0; i < kk.N; i++ {
		for j := 0; j < kk.N; j++ {
			if i != j {
				kk.D_ij[i][j] = kk.N + 1
			}
		}
	}
	for i := 0; i < kk.M; i++ {
		kk.D_ij[kk.Edge[i].Source-1][kk.Edge[i].Target-1] = 1
		kk.D_ij[kk.Edge[i].Target-1][kk.Edge[i].Source-1] = 1
	}
	// Floyd-Warshall for d_ij
	for k := 0; k < kk.N; k++ {
		for i := 0; i < kk.N; i++ {
			for j := 0; j < kk.N; j++ {
				if kk.D_ij[i][j] > kk.D_ij[i][k]+kk.D_ij[k][j] {
					kk.D_ij[i][j] = kk.D_ij[i][k] + kk.D_ij[k][j]
				}
			}
		}
	}

	var L_0 float64 = kk.Display

	// Get max from D_ij
	var max int = 0
	for i := 0; i < kk.N; i++ {
		for j := 0; j < kk.N; j++ {
			if kk.D_ij[i][j] > max {
				max = kk.D_ij[i][j]
			}
		}
	}

	var L float64 = L_0 / float64(max)

	// Initialize L_ij
	kk.L_ij = make([][]float64, kk.N)
	for i := 0; i < kk.N; i++ {
		kk.L_ij[i] = make([]float64, kk.N)
	}
	for i := 0; i < kk.N; i++ {
		for j := 0; j < kk.N; j++ {
			if i != j {
				kk.L_ij[i][j] = float64(kk.D_ij[i][j]) * L
			}
		}
	}

	// Initialize K_ij
	kk.K_ij = make([][]float64, kk.N)
	for i := 0; i < kk.N; i++ {
		kk.K_ij[i] = make([]float64, kk.N)
	}
	for i := 0; i < kk.N; i++ {
		for j := 0; j < kk.N; j++ {
			if i != j {
				kk.K_ij[i][j] = kk.K / (float64(kk.D_ij[i][j]) * float64(kk.D_ij[i][j]))
			}
		}
	}

	// Initialize Deltas
	kk.Deltas = make([]float64, kk.N)

	// Initialize Append-s
	kk.Addendx = make([][]float64, kk.N)
	for i := range kk.Addendx {
		kk.Addendx[i] = make([]float64, kk.N)
	}
	kk.Addendy = make([][]float64, kk.N)
	for i := range kk.Addendy {
		kk.Addendy[i] = make([]float64, kk.N)
	}
	// Initialize derivatives
	kk.Dx = make([]float64, kk.N)
	kk.Dy = make([]float64, kk.N)

	// Initialize limit: default is 100 if not defined
	if kk.Limit == 0 {
		kk.Limit = 100
	}

}

// ############# FUNCTIONS ############# //
func (kk *KamadaKawai) get_original_coords(coords []Coord) {
	for i := 0; i < kk.N; i++ {
		kk.Coords[i].X = coords[i].X
		kk.Coords[i].Y = coords[i].Y
	}
}
func (kk *KamadaKawai) set_original_coords() []Coord {
	coords := make([]Coord, kk.N)
	for i := 0; i < kk.N; i++ {
		coords[i].X = kk.Coords[i].X
		coords[i].Y = kk.Coords[i].Y
	}
	return coords
}

func (kk *KamadaKawai) get_delta_m_y(d_m_x float64, d_m_y float64, d_m_xx float64, d_m_yy float64, d_m_xy float64) float64 {
	return (-(d_m_xy * d_m_x) + (d_m_xx * d_m_y)) / (-(d_m_xx * d_m_yy) + (d_m_xy * d_m_xy))
}
func (kk *KamadaKawai) get_delta_m_x(d_m_y float64, d_m_yy float64, d_m_xy float64, delta_y float64) float64 {
	return (-(d_m_y) - (d_m_yy * delta_y)) / (d_m_xy)
}

func (kk *KamadaKawai) get_derivative_x(m int64) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == int(m) {
			kk.Addendx[m][i] = 0.0
			continue
		}

		var dist_x float64 = kk.Coords[m].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[m].Y - kk.Coords[i].Y

		var addend float64 = kk.K_ij[m][i] * (dist_x - ((kk.L_ij[m][i] * dist_x) / (math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(1)/float64(2)))))
		if math.IsNaN(addend) {
			continue
		}
		kk.Addendx[m][i] = addend
		sum += addend
	}
	kk.Dx[m] = sum
	return sum
}
func (kk *KamadaKawai) get_derivative_y(m int64) float64 {
	var sum float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if i == int(m) {
			kk.Addendy[m][i] = 0.0
			continue
		}

		var dist_x float64 = kk.Coords[m].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[m].Y - kk.Coords[i].Y

		var addend float64 = kk.K_ij[m][i] * (dist_y - ((kk.L_ij[m][i] * dist_y) / (math.Pow(math.Pow(dist_x, 2)+math.Pow(dist_y, 2), float64(1)/float64(2)))))
		if math.IsNaN(addend) {
			continue
		}
		kk.Addendy[m][i] = addend
		sum += addend
	}
	kk.Dy[m] = sum
	return sum
}
func (kk *KamadaKawai) get_delta_m(m int64) float64 {
	return math.Sqrt(math.Pow(kk.get_derivative_x(m), 2) + math.Pow(kk.get_derivative_y(m), 2))
}

func (kk *KamadaKawai) get_deltas_seq() int64 {
	var delta_index int64 = -1
	var max_delta float64 = 0.0

	for i := 0; i < kk.N; i++ {
		kk.Deltas[i] = kk.get_delta_m(int64(i))

		if kk.Deltas[i] > kk.Epsilon {
			if kk.Deltas[i] > max_delta {
				max_delta = kk.Deltas[i]
				delta_index = int64(i)
			}
		}
	}

	return delta_index
}

func (kk *KamadaKawai) get_addend_x(m int64, index int64) float64 {
	var dist_x float64 = kk.Coords[index].X - kk.Coords[m].X
	var dist_y float64 = kk.Coords[index].Y - kk.Coords[m].Y

	var addend float64 = kk.K_ij[index][m] * (dist_x - ((kk.L_ij[index][m] * dist_x) / (math.Sqrt(math.Pow(dist_x, 2) + math.Pow(dist_y, 2)))))
	if math.IsNaN(addend) {
		return 0.0
	}
	return addend
}
func (kk *KamadaKawai) get_addend_y(m int64, index int64) float64 {
	var dist_x float64 = kk.Coords[index].X - kk.Coords[m].X
	var dist_y float64 = kk.Coords[index].Y - kk.Coords[m].Y

	var addend float64 = kk.K_ij[index][m] * (dist_y - ((kk.L_ij[index][m] * dist_y) / (math.Sqrt(math.Pow(dist_x, 2) + math.Pow(dist_y, 2)))))
	if math.IsNaN(addend) {
		return 0.0
	}
	return addend
}

func (kk *KamadaKawai) update_delta_m(m int64, index int64) float64 {
	var tempx float64 = kk.get_addend_x(m, index)
	var tempy float64 = kk.get_addend_y(m, index)

	kk.Dx[index] = kk.Dx[index] - kk.Addendx[index][m] + tempx
	kk.Dy[index] = kk.Dy[index] - kk.Addendy[index][m] + tempy

	kk.Addendx[index][m] = tempx
	kk.Addendy[index][m] = tempy

	return math.Sqrt(math.Pow(kk.Dx[index], 2) + math.Pow(kk.Dy[index], 2))
}

func (kk *KamadaKawai) update_deltas_seq(m int64) int64 {
	var delta_index int64 = -1
	var max_delta float64 = 0.0

	for i := 0; i < kk.N; i++ {
		if m == int64(i) {
			continue
		}
		kk.Deltas[i] = kk.update_delta_m(m, int64(i))

		if kk.Deltas[i] > kk.Epsilon {
			if kk.Deltas[i] > max_delta {
				max_delta = kk.Deltas[i]
				delta_index = int64(i)
			}
		}
	}

	return delta_index
}

func (kk *KamadaKawai) get_derivatives_seq(m int64) (float64, float64, float64, float64, float64) {
	var d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m = 0.0, 0.0, 0.0, 0.0, 0.0

	for i := 0; i < kk.N; i++ {
		if i == int(m) {
			continue
		}

		var dist_x float64 = kk.Coords[m].X - kk.Coords[i].X
		var dist_y float64 = kk.Coords[m].Y - kk.Coords[i].Y

		var x2 float64 = math.Pow(dist_x, 2)
		var y2 float64 = math.Pow(dist_y, 2)
		var x2_y2 float64 = x2 + y2
		var x2_y2_1_2 float64 = math.Pow(x2_y2, float64(1)/float64(2))
		var x2_y2_3_2 float64 = math.Pow(x2_y2, float64(3)/float64(2))

		var addx = kk.K_ij[m][i] * (dist_x - ((kk.L_ij[m][i] * dist_x) / x2_y2_1_2))
		var addy = kk.K_ij[m][i] * (dist_y - ((kk.L_ij[m][i] * dist_y) / x2_y2_1_2))
		var addxx = kk.K_ij[m][i] * (1 - ((kk.L_ij[m][i] * y2) / x2_y2_3_2))
		var addyy = kk.K_ij[m][i] * (1 - ((kk.L_ij[m][i] * x2) / x2_y2_3_2))
		var addxy = kk.K_ij[m][i] * ((kk.L_ij[m][i] * dist_x * dist_y) / x2_y2_3_2)

		if !math.IsNaN(addx) {
			d_x_m += addx
		}
		if !math.IsNaN(addy) {
			d_y_m += addy
		}
		if !math.IsNaN(addxx) {
			d_xx_m += addxx
		}
		if !math.IsNaN(addyy) {
			d_yy_m += addyy
		}
		if !math.IsNaN(addxy) {
			d_xy_m += addxy
		}

	}
	return d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m
}
func (kk *KamadaKawai) get_derivatives_par(m int64) (float64, float64, float64, float64, float64) {
	var d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m float64
	var wg sync.WaitGroup
	var mu sync.Mutex

	for i := 0; i < kk.N; i++ {
		if i == int(m) {
			continue
		}

		wg.Add(1)
		go func(i int) {
			defer wg.Done()

			kk.mu.RLock()
			dist_x := kk.Coords[m].X - kk.Coords[i].X
			dist_y := kk.Coords[m].Y - kk.Coords[i].Y
			kk.mu.RUnlock() // <-- fix here

			x2 := dist_x * dist_x
			y2 := dist_y * dist_y
			x2_y2 := x2 + y2
			x2_y2_1_2 := math.Sqrt(x2_y2)
			x2_y2_3_2 := math.Pow(x2_y2, 1.5)

			k := kk.K_ij[m][i]
			l := kk.L_ij[m][i]

			addx := k * (dist_x - ((l * dist_x) / x2_y2_1_2))
			addy := k * (dist_y - ((l * dist_y) / x2_y2_1_2))
			addxx := k * (1 - ((l * y2) / x2_y2_3_2))
			addyy := k * (1 - ((l * x2) / x2_y2_3_2))
			addxy := k * ((l * dist_x * dist_y) / x2_y2_3_2)

			mu.Lock()
			if !math.IsNaN(addx) {
				d_x_m += addx
			}
			if !math.IsNaN(addy) {
				d_y_m += addy
			}
			if !math.IsNaN(addxx) {
				d_xx_m += addxx
			}
			if !math.IsNaN(addyy) {
				d_yy_m += addyy
			}
			if !math.IsNaN(addxy) {
				d_xy_m += addxy
			}
			mu.Unlock()
		}(i)
	}

	wg.Wait()
	return d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m
}
