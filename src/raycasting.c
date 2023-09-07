/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/09/01 12:28:23 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int mapHasWallAt(t_my_map *src,float x, float y) 
{
    if (x < 0 || x > src->windows_w || y < 0 || y > src->windows_h) {
        return 1;
    }
    int mapGridIndexX = (int)floor(x / SIZE);
    int mapGridIndexY = (int)floor(y / SIZE);
    if(src->map_2[mapGridIndexY][mapGridIndexX] == '1')
        return 1;
    return 0;
}

float corrValue(float rayangle)
{
    rayangle = remainder(rayangle,TWOPI);
    if(rayangle < 0)
        rayangle = TWOPI + rayangle;
    return (rayangle);
}
/* UP DOWN */
int rayfacingUD(float rayangle)
{
    if(rayangle > 0 && rayangle < PI)
        return 1;
    return 0;
}
/* Right Left */
int rayfacingRL(float rayangle)
{
    if(rayangle < 0.5 *PI || rayangle > 1.5*PI)
        return 1;
    return 0;
}

float distancebetweenPoint(float x1,float y1,float x2,float y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
void horizontalfunction(t_my_map *src,float rayangle,t_tocheck *ptr)
{
    float xtocheck;
    float ytocheck;
    
    ptr->y = floor(src->player_y / SIZE) * SIZE;
    if(ptr->facingdw)
        ptr->y += SIZE;
    ptr->x = src->player_x + (ptr->y - src->player_y) / tan(rayangle);
    ptr->deltay = SIZE;
    if(ptr->facingup)
        ptr->deltay*=-1;
    ptr->deltax = SIZE / tan(rayangle);
    if(ptr->facingleft && ptr->deltax > 0)
        ptr->deltax *= -1;
    if(ptr->facingright && ptr->deltax < 0)
        ptr->deltax *= -1;
    while(ptr->x >= 0 && ptr->x <= src->windows_w && ptr->y >=0 && ptr->y <= src->windows_h)
    {
        ytocheck = ptr->y;
        if(ptr->facingup)
            ytocheck -=1;
        if(mapHasWallAt(src,ptr->x,ytocheck))
        {
            ptr->horz_hitx = ptr->x;
            ptr->horz_hity = ptr->y;
            ptr->horz_content = src->map_2[(int)floor(ytocheck / SIZE)][(int)floor(ptr->x / SIZE)];
            ptr->foundh_hit = 1;
            break;
        }
        else
        {
            ptr->x += ptr->deltax;
            ptr->y += ptr->deltay; 
        }
    }
}

void verticalfunction(t_my_map *src,float rayangle,t_tocheck *ptr)
{
    float xtocheck;

    ptr->foundv_hit = 0; //found vertical wall hit
    ptr->vert_hitx = 0;
    ptr->vert_hity = 0;
    ptr->vert_content='0';
    ptr->x = floor(src->player_x / SIZE) * SIZE;
    if(ptr->facingright)
        ptr->x += SIZE;
    ptr->y = src->player_y + (ptr->x - src->player_x) * tan(rayangle);
    ptr->deltax = SIZE;
    if(ptr->facingleft)
        ptr->deltax*=-1;
    ptr->deltay = SIZE * tan(rayangle);
    if(ptr->facingup && ptr->deltay > 0)
        ptr->deltay *= -1;
    if(ptr->facingdw && ptr->deltay < 0)
        ptr->deltay *= -1;
    while(ptr->x >= 0 && ptr->x <= src->windows_w && ptr->y >=0 && ptr->y <= src->windows_h)
    {
        xtocheck = ptr->x;
        if(ptr->facingleft)
            xtocheck -=1;
        if(mapHasWallAt(src,xtocheck,ptr->y))
        {
            ptr->vert_hitx = ptr->x;
            ptr->vert_hity = ptr->y;
            ptr->vert_content = src->map_2[(int)floor(ptr->y / SIZE)][(int)floor(xtocheck / SIZE)];
            ptr->foundv_hit = 1;
            break;
        }
        else
        {
            ptr->x += ptr->deltax;
            ptr->y += ptr->deltay; 
        }
    }
}

void one_ray(t_my_map *src,float rayangle,int index)
{
    t_tocheck ptr;
    float dh; // Hor_distance
    float dv; // Ver_distance

    ptr.foundh_hit = 0;
    ptr.horz_hitx = 0;
    ptr.horz_hity = 0;
    ptr.horz_content='0';
    rayangle = corrValue(rayangle);
    ptr.facingdw = rayfacingUD(rayangle);
    ptr.facingup = !ptr.facingdw;
    ptr.facingright = rayfacingRL(rayangle);
    ptr.facingleft = !ptr.facingright;
    horizontalfunction(src,rayangle,&ptr);
    verticalfunction(src,rayangle,&ptr);
    if(ptr.foundh_hit)
        dh = distancebetweenPoint(src->player_x,src->player_y,ptr.horz_hitx,ptr.horz_hity);
    else
        dh = INT_MAX;
    if(ptr.foundv_hit)
       dv = distancebetweenPoint(src->player_x,src->player_y,ptr.vert_hitx,ptr.vert_hity);
    else
        dv = INT_MAX;
    
    if(dv < dh)
    {
        src->ray[index].dist = dv;
        src->ray[index].dist = src->ray[index].dist*cos(rayangle - src->rangle);
        src->ray[index].hitX = ptr.vert_hitx;
        src->ray[index].hitY = ptr.vert_hity;
        src->ray[index].hitContent = ptr.vert_content;
        src->ray[index].hitvert = 1;
    }
    else
    {
        src->ray[index].dist = dh;
        src->ray[index].dist = src->ray[index].dist*cos(rayangle - src->rangle);
        src->ray[index].hitX = ptr.horz_hitx;
        src->ray[index].hitY = ptr.horz_hity;
        src->ray[index].hitContent = ptr.horz_content;
        src->ray[index].hitvert = 0;
    }
    src->ray[index].rayalpha = rayangle;
    src->ray[index].facinDW = ptr.facingdw;
    src->ray[index].facingUP = ptr.facingup;
    src->ray[index].facinLeft = ptr.facingleft;
    src->ray[index].facinRight = ptr.facingright;
}

void ray_cast(t_my_map *src)
{
    float rayangle;
    int i;
    
    rayangle = src->rangle - HALF_FOV;
    i = 0;
    while(i < src->casted_rays)
    {
        one_ray(src,rayangle,i);
        rayangle += src->step_angle;
        i++;
    }
}
/* Drawing Rays */
void render_rays(t_my_map *src)
{
    int i;
    float wallstri;
    i = 0;
    ray_cast(src);
    while(i < src->casted_rays)
    {
        wallstri = (SIZE / src->ray[i].dist)*src->screen_dist;
        draw_square(src,i*1,(HEIGHT/2 - wallstri/2),i+1,(HEIGHT/2 - wallstri/2)+wallstri,YELLOW);
        i++;
    }
}
void render_rays2(t_my_map *src)
{
    int i;

    i = -1;
    ray_cast(src);
    while(++i < src->casted_rays)
        line(src,src->player_x/4,src->player_y/4,src->ray[i].hitX/4,src->ray[i].hitY/4,YELLOW);
}
void minimapmini(t_my_map *src)
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
                draw_square(src,j * SIZE/4,i * SIZE/4,((j * SIZE/4)+SIZE/4),((i * SIZE/4)+SIZE/4),0xc8c8c8);
            else
                draw_square(src,j * SIZE/4,i * SIZE/4,((j * SIZE/4)+SIZE/4),((i * SIZE/4)+SIZE/4),0x646464);
            
            j++;
        }
        i++;
    }
    // draw_circle(src,src->player_x/4,src->player_y/4,4);
    render_rays2(src);
    mlx_put_image_to_window(src->mlx, src->win, src->img.img, 0, 0);
}

void minimap(t_my_map *src)
{
    int i;
    int j;
    
    i = 0;
    render_rays(src);
    // minimapmini(src);    
    mlx_put_image_to_window(src->mlx, src->win, src->img.img, 0, 0);
}

void init_player(t_my_map *src)
{
    src->player_x =  src->col_player * SIZE;
    src->player_y =  src->row_player * SIZE;
    src->casted_rays = WIDTH;
    src->step_angle = FOV / src->casted_rays;
    src->ray = malloc(src->casted_rays*sizeof(t_ray));
    src->screen_dist = (WIDTH/2) / tan(HALF_FOV);
    src->up_down = 0;
    src->left_right = 0;
    src->rangle = PI / 2;
    src->wspeed = 2.0;
    src->tspeed = 1.5 * (PI / 180);
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
	src->win = mlx_new_window(src->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!src->win)
		return (1);
    init_player(src);
    return (0);   
}

void raycasting(t_my_map *src)
{
    init_value(src);
    src->img.img = mlx_new_image(src->mlx, WIDTH, HEIGHT);
	src->img.addr = mlx_get_data_addr(src->img.img, &src->img.bits_per_pixel, &src->img.line_length,&src->img.endian);
    minimap(src);
    mlx_hook(src->win,KEYPRESS,(1L<<0),&player_press,src);
    mlx_hook(src->win,KEYUP,(1L<<1),&player_up,src);
    mlx_loop(src->mlx);
}