/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:29:07 by abenlahb          #+#    #+#             */
/*   Updated: 2023/09/01 10:08:51 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	player_move(t_my_map *player)
{
    float nextMove;
    float a;
    float b;
    mlx_destroy_image(player->mlx,player->img.img);
    player->img.img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
    player->rangle += player->left_right * player->tspeed;
    nextMove = player->up_down * player->wspeed;

    a = player->player_x + cos(player->rangle)*nextMove;
    b = player->player_y + sin(player->rangle)*nextMove;
    // printf("%d\n",mapHasWallAt(player,a,b));
    if(!mapHasWallAt(player,a,b))
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