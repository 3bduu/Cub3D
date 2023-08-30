/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:29:07 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/30 12:23:31 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	player_move(t_my_map *player)
{
    float nextMove;
    float a;
    float b;
    mlx_destroy_image(player->mlx,player->img.img);
    player->img.img = mlx_new_image(player->mlx, player->windows_w, player->windows_h);
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
    return 0;
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
    return 0;
}