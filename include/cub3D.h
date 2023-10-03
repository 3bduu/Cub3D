#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
#include "../libft/libft.h"
#include<mlx.h>
// #include "../minilibx-linux/mlx.h"
#include <math.h>
//# include "./get_next/get_next_line.h"





# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO"
# define EAST_TEXTURE "EA"
# define WEST_TEXTURE "WE"
#define TEXTURE_EXTENSION ".xpm"
#define F_COLOR "F"
#define C_COLOR "C"

#define GREEN  0x0aad39
#define RED    0xc70c1c
#define YELLOW 0xdbd112
#define ORANGE 0Xfa8202
#define BLACK  0x000000
#define BLUE   0x818589
#define WHITE  0xFFFFFF
#define WIDTH 1024
#define HEIGHT 700

#define SIZE 40
#define PI 3.14159265359
#define TWOPI 6.28318530718
#define FOV (60 * (PI / 180))
#define HALF_FOV (FOV / 2)

#define KEYPRESS 2
#define KEYUP 3
#define W 119
#define A 97
#define S 115
#define D 100
#define ESC 65307
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;
// typedef struct s_images
// {
// 	void	*img;
// 	char	*addres;
	
// }	t_img;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_tocheck
{
    int facingdw;
    int facingup;
    int facingright;
    int facingleft;
    float x;
    float y;
    float deltax;
    float deltay;
    int foundh_hit;
    float horz_hitx;
    float horz_hity;
    char     horz_content;
    int foundv_hit; //found vertical wall hit
    float vert_hitx;
    float vert_hity;
    char    vert_content;
    
}   t_tocheck;


typedef struct s_ray
{
    float rayalpha;
    float hitX; //wall HitX
    float hitY; // Wall hitY
    float dist; //distance
    int hitvert; //wasHitVertical
    int facingUP; //is ray facing up
    int facinDW; //is ray facing down
    int facinLeft; // is ray facing left
    int facinRight; // is ray facing right
    int hitContent; // us wall hit Content
    t_data data[4];
}           t_ray;

typedef struct s_get_map
{
    char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
    int         column;
    char    pos_player;
    int     row_player;
    int     col_player;
    char        **map;
    char        **map_2;
    int nb_raw;
    int nb_line;
    int nb_map2;
    int biger_row;
    t_color f_color;
    t_color c_color;
    //     Raycasting
    void         *mlx;
    void         *win;
    int             i;
    int     windows_w;
    int     windows_h;
    int     casted_rays;
    float   step_angle;
    float     player_x;
    float     player_y;
    float   up_down;
    float   left_right;
    float   rangle; //rotation angle
    float   wspeed; //walk speed
    float   tspeed; // turn speed
    float   start_angle;
    float screen_dist;
    // RAY //
    t_ray  *ray;
    uint32_t *colorBuffer;
    t_data img;
}   	t_my_map;

/*  Raycasting*/


///===> this for parsing 
//utils
unsigned int *my_mlx_pixel_get(t_data *data, int x, int y);
void check_map(t_my_map *src);
int	is_char_pattern(char c, char *set);
char *ft_strcpy(char *dest,  char *src);
int count_longest_line(char **map);
char *ft_strlen_dup(const char *s1, size_t len);
void check2_map(t_my_map *src);
void get_map(t_my_map *src);
int isspace(int c);
int	is_videe(char *s);
char	*ft_str_n_dup(const char *s1, size_t len);
int test_is_derctory(char *file_name);
int is_empty(int fd);
int test_extension_xpm(char *file_name, char *extension);
int test_extension(char *file_name, char *extension) ;
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
void line(t_my_map *src, int start_x, int start_y, int end_x, int end_y,int color);
void    raycasting(t_my_map *src);
void minimap(t_my_map *src);
int     player_press(int keycode,t_my_map *src);
int     player_up(int keycode,t_my_map *src);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_square(t_my_map *src,float start_h,float start_w,float end_h,float end_w,int color);
void    draw_circle(t_my_map *src,int posX,int posY,int ray);
int mapHasWallAt(t_my_map *src,float x, float y) ;
#endif