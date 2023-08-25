/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb < abenlahb@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/24 19:24:44 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_rectangle(t_my_map *src,int start_h,int start_w,int end_h,int end_w){

    int x;
    while(start_h < end_h)
    {
        x = start_w;
        while(x < end_w)
        {
            mlx_pixel_put(src->mlx,src->win,start_h,x,0xFFFFFF);
            x++;
        }
        start_h++;
    }
}

void draw_map2d(t_my_map *src,int map[ROWS][COLS])
{
    int i;
    int j;

    i = 0;
    while(i < ROWS)
    {
        j = 0;
        while(j < COLS)
        {
            src->height = j * SIZE;
            src->weight = i * SIZE;
            if(map[i][j] == 1)
                draw_rectangle(src,src->height,src->weight,(src->height+SIZE),(src->weight+SIZE));
            j++;
        }
        i++;
    }
}
/* Delta Time to make the Game STABLE for ALL FPS*/

void deltatime_forgame(t_my_map *src)
{
    float deltatime;
    
    src->tofl_frame = 0;
    deltatime = current_time() - src->tofl_frame;
    src->tofl_frame = current_time();
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
    src->windows_w = COLS*SIZE;
    src->windows_h = ROWS*SIZE;
    src->rays = src->windows_w;
    src->player_x = src->windows_w ;
    src->player_y = src->windows_h;
    src->up_down = 0;
    src->left_right = 0;
    src->rAngle = PI / 2;
    src->wSpeed = 100;
    src->tSpeed = 45 * (PI / 180);
    src->win = mlx_new_window(src->mlx,src->windows_w,src->windows_h,"Cub3D");
    
    draw_map2d(src,map);
    deltatime_forgame(src);
    line(src,src->player_x*0.5,src->player_y*0.5,(src->player_x+cos(src->rAngle)*40)*0.5,(src->player_y+sin(src->rAngle)*40)*0.5);
    mlx_hook(src->win,KEYPRESS,(1L<<0),&player_hooks,src);
    mlx_loop(src->mlx);
}