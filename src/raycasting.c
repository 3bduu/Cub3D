/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb < abenlahb@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/23 22:06:32 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_rectangle(t_my_map *vars,int y,int x,int c) {
	int x_end = x * SIZE;
	int y_end = y * SIZE;

	while (y < y_end) {
		int i = x;
		while (i < x_end) {
			mlx_pixel_put(vars->mlx, vars->win, i, y, c);
			i++;
		}
		y++;
	}
}

void raycasting(t_my_map *src)
{
    int map[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
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
    src->windows_w = ROWS*SIZE;
    src->windows_h = COLS*SIZE;
    src->win = mlx_new_window(src->mlx,src->windows_h,src->windows_w,"Cub3D");

    void my_mlx_rectangle(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) {
    int x, y;

    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        }
    }
}
   
    int x, y;

    for (y = 0; y < ROWS; y++) {
        for (x = 0; x < COLS; x++) {
            int x1 = x * SIZE;
            int y1 = y * SIZE;
            int x2 = x1 + SIZE;
            int y2 = y1 + SIZE; 
            if (map[y][x] == 1) {
                my_mlx_rectangle(src->mlx,src->win,x1,y1,x2,y2,255);// White for 1
            }
        }
    
    }
    mlx_loop(src->mlx);
}