/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:36:46 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/30 12:31:12 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_my_map *src,int start_h,int start_w,int end_h,int end_w,int color){

    int x;
    
    while(start_h < end_h)
    {
        x = start_w;
        while(x < end_w)
        {
            my_mlx_pixel_put(&src->img,start_h,x,color);
            x++;
        }
        start_h++;
    }
}

/* Euclidean Distance */
void draw_circle(t_my_map *src,int posX,int posY,int ray)
{
    int dx;
    int dy;
    int x;
    int y;
    y = posY - ray;
    while(y <= posY + ray)
    {
        x = posX - ray;
        while(x <= posX + ray)
        {
            dx = x - posX;
            dy = y - posY;
            if(sqrt(dx*dx+dy*dy)<=ray)
             my_mlx_pixel_put(&src->img,x,y,RED);
            x++;
        }
        y++;
    }
}

/*  Bresenham's line algorithm. */
void line(t_my_map *src, int start_x, int start_y, int end_x, int end_y,int color)
{
    float incre_x;
    float incre_y;
    int steps;
    float x;
    float y;
    int dx;
    int dy;
    int i;
    
    dx = end_x - start_x;
    dy = end_y - start_y;
    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    incre_x = (float)dx / steps;
    incre_y = (float)dy / steps;
    x = start_x;
    y = start_y;

    mlx_pixel_put(src->mlx, src->win, x, y, color);
    i = -1;
    while (++i < steps) {
        x += incre_x;
        y += incre_y;
        my_mlx_pixel_put(&src->img,x, y, color);
    }
}