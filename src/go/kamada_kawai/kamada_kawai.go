package main

type Coord struct {
	X float64 `json:"x"`
	Y float64 `json:"y"`
}

type Edge struct {
	Source int `json:"source"`
	Target int `json:"target"`
}

type KamadaKawai struct {
	N       int
	Coords  []Coord `json:"coords"`
	M       int
	Edge    []Edge `json:"edges"`
	D_ij    [][]int
	L_ij    [][]float64
	K_ij    [][]float64
	K       float64 `json:"K"`
	Epsilon float64 `json:"epsilon"`
	Display float64 `json:"display"`
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

}
