#include <stdbool.h>

#include "../kamada_kawai.h"

void mlt_seq(KamadaKawai *kk)
{
    int delta_max_index = get_deltas_seq(kk);

    while (delta_max_index != -1)
    {
        int steps = kk->limit;
        while (true)
        {
            bool equilibrium = true;

            for (int i = 0; i < kk->n; i++)
            {
                double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
                get_derivatives_seq(kk, i, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

                double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
                double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
                kk->coords[i].x += delta_x;
                kk->coords[i].y += delta_y;

                kk->deltas[i] = get_delta_m(kk, i);
            }

            for (int i = 0; i < kk->n; i++)
                if (kk->deltas[i] > kk->epsilon)
                    equilibrium = false;

            if (equilibrium)
                break;
            if (steps-- <= 0)
                break;
        }

        int temp = get_deltas_seq(kk);
        if (temp == delta_max_index)
            break;
        delta_max_index = temp;
    }

    return;
}