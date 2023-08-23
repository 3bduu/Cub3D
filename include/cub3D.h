#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
//# include "./get_next/get_next_line.h"



# define FLOOR "F"
# define CEILLING "C"

# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO"
# define EAST_TEXTURE "EA"
# define WEST_TEXTURE "WE"
#define TEXTURE_EXTENSION ".xpm"
//Raycasting PART
#define SIZE 50;
#define ROWS 13
#define COLS 20
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
    void         *mlx;
    void         *win;
    int     windows_w;
    int     windows_h;
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
void raycasting(t_my_map *src);
#endif