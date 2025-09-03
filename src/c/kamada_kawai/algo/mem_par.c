#include <stdbool.h>
#include <omp.h>
#include <stdio.h>

#include "../kamada_kawai.h"

void mem_par(KamadaKawai *kk)
{
    int delta_max_index = get_deltas_mem_par(kk); // no convinent speedup

    while (delta_max_index != -1)
    {
        double steps = kk->limit;
        while (kk->deltas[delta_max_index] > kk->epsilon)
        {
            double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
            get_derivatives_mem_par(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m); // at first seeable speedup, then progressively worse overhead with more threads

            double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
            double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            kk->deltas[delta_max_index] = get_delta_m_mem_par(kk, delta_max_index);

            steps -= 1;
            if (steps <= 0)
            {
                break;
            }
        }

        int temp = update_deltas_mem_par(kk, delta_max_index);
        if (temp == delta_max_index)
        {
            break;
        }
        delta_max_index = temp;
    }

    return;
}