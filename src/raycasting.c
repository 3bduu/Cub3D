/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb < abenlahb@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:42:24 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/31 18:39:07 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int mapHasWallAt(t_my_map *src,float x, float y) {
    if (x < 0 || x > src->windows_w || y < 0 || y > src->windows_h) {
        return 1;
    }
    int mapGridIndexX = floor(x / SIZE);
    int mapGridIndexY = floor(y / SIZE);
    if(src->map_2[mapGridIndexY][mapGridIndexX]!='0')
        return 1;
    return 0;
}

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
        return 1;
    return 0;
}
/* Right Left */
int rayfacingRL(float rayAngle)
{
    if(rayAngle < 0.5 *PI || rayAngle > 1.5*PI)
        return 1;
    return 0;
}

float distancebetweenPoint(int x1,int y1,int x2,int y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
void one_ray(t_my_map *src,float rayAngle,int index)
{
    int isfacingDW;
    int isfacingUP;
    int isfacingRight;
    int isfacingLeft;
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
    int foundHhit = 0; //found horz wall hit
    float horzhitX = 0;
    float horzhitY = 0;
    char     horzwallcontent='0';
    
    rayAngle = corrValue(rayAngle);
    isfacingDW = rayfacingUD(rayAngle);
    isfacingUP = !isfacingDW;
    isfacingRight = rayfacingRL(rayAngle);
    isfacingLeft = !isfacingRight;
    //the y coord
    yintercept = floor(src->player_y / SIZE) * SIZE;
    if(isfacingDW)
        yintercept += SIZE;
    //the x coord
    xintercept = src->player_x + (yintercept - src->player_y) / tan(rayAngle);
    // calculate xstep and ystep
    ystep = SIZE;
    if(isfacingUP)
        ystep*=-1;
    xstep = SIZE / tan(rayAngle);
    if(isfacingLeft && xstep > 0)
        xstep *= -1;
    if(isfacingRight && xstep < 0)
        xstep *= -1;
    float nextHorztouchX = xintercept;
    float nextHorztouchY = yintercept;
    //incremant xstep and ystep until we find a wall
    while(nextHorztouchX >= 0 && nextHorztouchX <= src->windows_w && nextHorztouchY >=0 && nextHorztouchY <= src->windows_h)
    {
        float xtocheck = nextHorztouchX;
        float ytocheck = nextHorztouchY;
        if(isfacingUP)
            ytocheck -=1;
        if(mapHasWallAt(src,xtocheck,ytocheck))
        {
            horzhitX = nextHorztouchX;
            horzhitY = nextHorztouchY;
            horzwallcontent = src->map_2[(int)floor(ytocheck / SIZE)][(int)floor(xtocheck / SIZE)];
            foundHhit = 1;
            break;
        }
        else
        {
            nextHorztouchX += xstep;
            nextHorztouchY += ystep; 
        }
    }
    //----------------------------------------VERTICAL-------------------
    int foundVhit = 0; //found vertical wall hit
    float verthitX = 0;
    float verthitY = 0;
    char    vertwallcontent='0';
    
    //the x coord
    xintercept = floor(src->player_x / SIZE) * SIZE;
    if(isfacingRight)
        xintercept += SIZE;
    //the y coord
    yintercept = src->player_y + (xintercept - src->player_x) / tan(rayAngle);
    // calculate xstep and ystep
    xstep = SIZE;
    if(isfacingLeft)
        xstep*=-1;
    ystep = SIZE / tan(rayAngle);
    if(isfacingUP && ystep > 0)
        ystep *= -1;
    if(isfacingDW && ystep < 0)
        ystep *= -1;
    float nextverttouchX = xintercept;
    float nextverttouchY = yintercept;
    //incremant xstep and ystep until we find a wall
    while(nextverttouchX >= 0 && nextverttouchX <= src->windows_w && nextverttouchY >=0 && nextverttouchY <= src->windows_h)
    {
        float xtocheck = nextverttouchX;
        float ytocheck = nextverttouchY;
        if(isfacingLeft)
            xtocheck -=1;
        if(mapHasWallAt(src,xtocheck,ytocheck))
        {
            verthitX = nextverttouchX;
            verthitY = nextverttouchY;
            vertwallcontent = src->map_2[(int)floor(ytocheck / SIZE)][(int)floor(xtocheck / SIZE)];
            foundVhit = 1;
            break;
        }
        else
        {
            nextverttouchX += xstep;
            nextverttouchY += ystep; 
        }
    }
    
    float horzhitDistance;
    if(foundHhit)
        horzhitDistance = distancebetweenPoint(src->player_x,src->player_y,horzhitX,horzhitY);
    else
        horzhitDistance = INT_MAX;
    float verthitDistance;
    if(foundVhit)
       verthitDistance = distancebetweenPoint(src->player_x,src->player_y,verthitX,verthitY);
    else
        verthitDistance = INT_MAX;
    
    if(verthitDistance < horzhitDistance)
    {
        src->ray[index].dist = verthitDistance;
        src->ray[index].hitX = verthitX;
        src->ray[index].hitY = verthitY;
        src->ray[index].hitContent = vertwallcontent;
        src->ray[index].hitvert = 1;
    }
    else
    {
        src->ray[index].dist = horzhitDistance;
        src->ray[index].hitX = horzhitX;
        src->ray[index].hitY = horzhitY;
        src->ray[index].hitContent = horzwallcontent;
        src->ray[index].hitvert = 0;
    }
    src->ray[index].rayalpha = rayAngle;
    src->ray[index].facinDW = isfacingDW;
    src->ray[index].facingUP = isfacingUP;
    src->ray[index].facinLeft = isfacingLeft;
    src->ray[index].facinRight = isfacingRight;
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
	while (src->map_2[src->i])
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
    src->ray = malloc(src->casted_rays*sizeof(t_ray));
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