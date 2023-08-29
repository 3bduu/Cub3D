/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/29 13:10:29 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_my_map *src,int start_h,int start_w,int end_h,int end_w){

    int x;
    while(start_h < end_h)
    {
        x = start_w;
        while(x < end_w)
        {
            my_mlx_pixel_put(&src->img,start_h,x,0xFFFFFF);
            x++;
        }
        start_h++;
    }
}

void draw_map2d(t_my_map *src,int map[ROWS][COLS])
{
    int i;
    int j;
	src->img.img = mlx_new_image(src->mlx, src->windows_w, src->windows_h);
	src->img.addr = mlx_get_data_addr(src->img.img, &src->img.bits_per_pixel, &src->img.line_length,
								&src->img.endian);
    i = 0;
    while(i < ROWS)
    {
        j = 0;
        while(j < COLS)
        {
            src->height = j * SIZE;
            src->weight = i * SIZE;
            if(map[i][j] == 1)
                draw_square(src,src->height,src->weight,(src->height+SIZE),(src->weight+SIZE));
            j++;
        }
        i++;
    }
    line(src,src->player_x,src->player_y,(src->player_x+cos(src->rAngle)*SIZE),(src->player_y+sin(src->rAngle)*SIZE));
    mlx_put_image_to_window(src->mlx, src->win, src->img.img, 0, 0);
}


void raycasting(t_my_map *src)
{
    int map[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    src->mlx = mlx_init();
    src->windows_w = COLS*SIZE;
    src->windows_h = ROWS*SIZE;
    src->rays = src->windows_w;
    src->player_x = src->windows_w / 2;
    src->player_y = src->windows_h / 2;
    src->up_down = 0;
    src->left_right = 0;
    src->rAngle = PI / 2;
    src->wSpeed = 2;
    src->tSpeed = 2 * (PI / 180);
    src->win = mlx_new_window(src->mlx,src->windows_w,src->windows_h,"Cub3D");
    draw_map2d(src,map);
    mlx_hook(src->win,KEYPRESS,(1L<<0),&player_press,src);
    mlx_hook(src->win,KEYUP,(1L<<1),&player_up,src);
    mlx_loop(src->mlx);
}