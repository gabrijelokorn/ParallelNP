#include <stdbool.h>
#include <omp.h>

#include "../kamada_kawai.h"

void sgl_par(KamadaKawai *kk)
{
    omp_set_nested(1);
    int delta_max_index = get_deltas_par(kk);

    while (delta_max_index != -1)
    {
        int steps = kk->limit;
        while (kk->deltas[delta_max_index] > kk->epsilon)
        {
            double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
            get_derivatives_par(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

            double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
            double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            kk->deltas[delta_max_index] = get_delta_m_par(kk, delta_max_index);
            if (steps-- <= 0)
                break;
        }

        int temp = update_deltas_par(kk, delta_max_index);
        if (temp == delta_max_index)
            break;
        delta_max_index = temp;
    }

    return;
}