/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/31 13:48:49 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float corrValue(float rayAngle)
{
    rayAngle = remainder(rayAngle,TWOPI);
    if(rayAngle < 0)
        rayAngle = TWOPI + rayAngle;
    return (rayAngle);
}
/* UP DOWN */
int rayfacingUD(float rayAngle)
{
    if(rayAngle > 0 && rayAngle < PI)
        return 1
    return 0;
}
/* Right Left */
int rayfacingRL(float rayAngle)
{
    if(rayAngle < 0.5 *PI || rayAngle > 1.5 PI)
        return 1
    return 0;
}

void one_ray(t_my_map *src,float rayAngle,int index)
{
    int isfacingDW;
    int isfacingUP;
    int isfacingRight;
    int isfacingLeft;
    float x
    int foundHhit = 0; //found horz wall hit
    float horzhitX;
    float horzhitY;
    int     horzwallcontent;
    
    rayAngle = corrValue(rayAngle);
    isfacingDW = rayfacingUD(rayAngle);
    isfacingUP = !isfacingDW;
    isfacingRight = rayfacingRL(rayAngle);
    isfacingLeft = !isfacingRight;

    hor = floor(src->player_y / SIZE) * SIZE;
    if()
    
}

void ray_cast(t_my_map *src)
{
    float rayAngle;
    int i;
    
    rayAngle = src->rAngle - HALF_FOV;
    i = 0;
    while(i < src->casted_rays)
    {
        one_ray(src,rayAngle,i);
        rayAngle += src->step_angle;
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
    line(src,src->player_x,src->player_y,(src->player_x+cos(src->rAngle)*SIZE),(src->player_y+sin(src->rAngle)*SIZE),YELLOW);
    mlx_put_image_to_window(src->mlx, src->win, src->img.img, 0, 0);
}

int init_value(t_my_map *src)
{
    src->i = 0;
    src->mlx = mlx_init();
	if (!src->mlx)
		return (1);
	src->windows_w = ft_strlen(src->map_2[0]) * SIZE;
	while (src->map_2[src->i])= src->rAngle - HALF_FOV
		src->i++;
	src->windows_h = src->i * SIZE;
	src->win = mlx_new_window(src->mlx, src->windows_w,
			src->windows_h, "Cub3d");
	if (!src->win)
		return (1);
    src->player_x = (float) src->col_player * SIZE;
    src->player_y = (float) src->row_player * SIZE;
    src->casted_rays = src->windows_w;
    src->step_angle = FOV / src->casted_rays;
    src->up_down = 0;
    src->left_right = 0;
    src->rayD = src->windows_w;
    src->rAngle = PI / 2;
    src->wSpeed = 2;
    src->tSpeed = 2 * (PI / 180);
    return (0);   
}
= src->rAngle - HALF_FOV
void raycasting(t_my_map *src)
{
    init_value(src);
    src->img.img = mlx_new_image(src->mlx, src->windows_w, src->windows_h);
	src->img.addr = mlx_get_data_addr(src->img.img, &src->img.bits_per_pixel, &src->img.line_length,&src->img.endian);
    minimap(src);
    mlx_hook(src->win,KEYPRESS,(1L<<0),&player_press,src);
    mlx_hook(src->win,KEYUP,(1L<<1),&player_up,src);
    mlx_loop(src->mlx);
}= src->rAngle - HALF_FOV