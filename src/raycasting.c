/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/30 12:37:09 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void ray_cast(t_my_map *src)
{
    int i;
    int j;
    float tar_x; //target_x
    float tar_y; //target_y
    int col;
    int row;
    
    i = 0;
    src->start_angle = src->rAngle - HALF_FOV; // define left most angle of FOV
    /*Draw rays*/
    while(i < CASTED_RAYS)
    {
        /*Draw one ray*/
        j = 0;
        while(j < src->rayD)
        {
            /* Get ray target cordinate */
            tar_x =  src->player_x + cos(src->start_angle)*j;
            tar_y =  src->player_y + sin(src->start_angle)*j;
            /* Get the index on the original map */
            col = (int)tar_x/SIZE;
            row = (int)tar_y/SIZE;
            if(src->map_2[row][col] == '1')
            {
                draw_square(src,col*SIZE,row*SIZE,col*SIZE+SIZE-1,row*SIZE+SIZE-1,ORANGE);
                line(src,src->player_x,src->player_y,tar_x,tar_y,YELLOW); /* Draw casted Ray  */
                break;
            }
            j++;
        }
        i++;
       src->start_angle += STEP_ANGLE;  //increment angle by a single step
    }
}

void minimap(t_my_map *src)
{
    int i;
    int j;
    
    i = 0;
    while(src->map_2[i])
    {
        j = 0;
        while(src->map_2[i][j])
        {
            if(src->map_2[i][j] == '1')
                draw_square(src,j * SIZE,i * SIZE,((j * SIZE)+SIZE-1),((i * SIZE)+SIZE-1),0xc8c8c8);
            else
                draw_square(src,j * SIZE,i * SIZE,((j * SIZE)+SIZE-1),((i * SIZE)+SIZE-1),0x646464);
            
            j++;
        }
        i++;
    }
    draw_circle(src,src->player_x,src->player_y,4);
    // line(src,src->player_x,src->player_y,(src->player_x+cos(src->rAngle)*20),(src->player_y+sin(src->rAngle)*20));
    ray_cast(src);
    mlx_put_image_to_window(src->mlx, src->win, src->img.img, 0, 0);
}

int init_value(t_my_map *src)
{
    src->i = 0;
    src->mlx = mlx_init();
	if (!src->mlx)
		return (1);
	src->windows_w = ft_strlen(src->map_2[0]) * SIZE;
	while (src->map_2[src->i])
		src->i++;
	src->windows_h = src->i * SIZE;
	src->win = mlx_new_window(src->mlx, src->windows_w,
			src->windows_h, "so_long");
	if (!src->win)
		return (1);
    src->player_x = (float) src->col_player * SIZE;
    src->player_y = (float) src->row_player * SIZE;
    src->up_down = 0;
    src->left_right = 0;
    src->rayD = src->windows_w;
    src->rAngle = PI / 2;
    src->wSpeed = 2;
    src->tSpeed = 2 * (PI / 180);
    return (0);   
}

void raycasting(t_my_map *src)
{
    init_value(src);
    src->img.img = mlx_new_image(src->mlx, src->windows_w, src->windows_h);
	src->img.addr = mlx_get_data_addr(src->img.img, &src->img.bits_per_pixel, &src->img.line_length,&src->img.endian);
    minimap(src);
    mlx_hook(src->win,KEYPRESS,(1L<<0),&player_press,src);
    mlx_hook(src->win,KEYUP,(1L<<1),&player_up,src);
    mlx_loop(src->mlx);
}