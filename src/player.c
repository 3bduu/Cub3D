/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb < abenlahb@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:29:07 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/29 19:17:40 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	player_move(t_my_map *player)
{
    float nextMove;
    float a;
    float b;
    
    player->rAngle += player->left_right * player->tSpeed;
    nextMove = player->up_down * player->wSpeed;

    a = player->player_x + cos(player->rAngle)*nextMove;
    b = player->player_y + sin(player->rAngle)*nextMove;
    if(player->map_2[(int)floor(b/SIZE)][(int)floor(a/SIZE)]!='1')
    {
        player->player_x = a;
        player->player_y = b;
    }
    
	mlx_clear_window(player->mlx, player->win);
    minimap(player);
}

int player_press(int keycode,t_my_map *src)
{
    if(keycode == W)
        src->up_down += 1;
    else if(keycode == S)
        src->up_down -= 1;
    else if(keycode == A)
        src->left_right -= 1;
    else if(keycode == D)
        src->left_right += 1;
    if(src->left_right || src->up_down)
        player_move(src);
}

int player_up(int keycode,t_my_map *src)
{
    if(keycode == W)
        src->up_down = 0;
    else if(keycode == S)
        src->up_down = 0;
    else if(keycode == A)
        src->left_right = 0;
    else if(keycode == D)
        src->left_right = 0;
}