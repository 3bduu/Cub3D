/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:36:46 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/29 13:06:51 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
/*  Bresenham's line algorithm. */

void line(t_my_map *src, int start_x, int start_y, int end_x, int end_y)
{
    int dx = end_x - start_x;
    int dy = end_y - start_y;
    int i = -1;
    int steps;
    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float incre_x = (float)dx / steps;
    float incre_y = (float)dy / steps;

    float x = start_x;
    float y = start_y;

    mlx_pixel_put(src->mlx, src->win, x, y, 0xFFFFFF);

    while (++i < steps) {
        x += incre_x;
        y += incre_y;
        my_mlx_pixel_put(&src->img,x, y, 0xFFFFFF);
    }
}