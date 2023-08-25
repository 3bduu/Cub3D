/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb < abenlahb@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:36:46 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/24 19:16:48 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double current_time()
{
    struct timeval t;
    gettimeofday(&t,NULL);
    return (double)t.tv_sec+(double)t.tv_usec / 1000000.0;
}

void line(t_my_map *src, int start_x, int start_y, int end_x, int end_y)
{
    int dx = end_x - start_x;
    int dy = end_y - start_y;
    int i = -1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float incre_x = (float)dx / steps;
    float incre_y = (float)dy / steps;

    float x = start_x;
    float y = start_y;

    mlx_pixel_put(src->mlx, src->win, x, y, 0xFFFFFF);

    while (++i < steps) {
        x += incre_x;
        y += incre_y;
        mlx_pixel_put(src->mlx, src->win, x, y, 0xFFFFFF);
    }
}