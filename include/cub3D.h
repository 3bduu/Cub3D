#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <sys/time.h>
#include <math.h>
//# include "./get_next/get_next_line.h"



# define FLOOR "F"
# define CEILLING "C"

# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO"
# define EAST_TEXTURE "EA"
# define WEST_TEXTURE "WE"
#define TEXTURE_EXTENSION ".xpm"
//Raycasting PART
/*  KEYCODE  */
#define KEYPRESS 2
#define KEYUP 3
#define W 119
#define A 97
#define S 115
#define D 100
#define ESC 65307

#define SIZE 50
#define ROWS 13
#define COLS 20
#define FPS 30
#define TFO_FRAME (1000 / FPS) //Time for ONE Frame
#define PI 3.14159265359
#define PI2 6.28318530718
#define FOV (60 * (PI / 180)) //Field of View

typedef struct s_get_map
{
    char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
    char **map;
    char **map_2;
    int nb_raw;
    int nb_line;
    //Raycasting PART
    void         *img;
    void         *mlx;
    void         *win;
    char	     *addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     windows_w;
    int     windows_h;
    int     height;
    int     weight;
    float     player_x;
    float     player_y;
    int     tofl_frame; //time of last frame
    int     rays;
    float   up_down;
    float   left_right;
    float   rAngle; //rotation angle
    float   wSpeed; //walk speed
    float   tSpeed; // turn speed

}   	t_my_map;

///===> this for parsing 
//utils
void	free_2p(char **array); 
char	*get_next_line(int fd);
int	ft_strcmp(char *s1, char *s2);
void start_parse( char *filename, t_my_map *src);
void let_dup(t_my_map *info_mapm, char *file_name);
int is_spacee(char c);
void start_parse(char *filename,t_my_map *src);
void  ft_putstr(char *str,int fd);
void error_message(char *str,int fd);
char **get_content(int fd, t_my_map *info_map);
/*  Raycasting   */
void line(t_my_map *src, int start_x, int start_y, int end_x, int end_y);
void    raycasting(t_my_map *src);
float deltatime_forgame(t_my_map *src);
double  current_time();
void    draw_map2d(t_my_map *src,int map[ROWS][COLS]);
int     player_press(int keycode,t_my_map *src);
int     player_up(int keycode,t_my_map *src);
#endif