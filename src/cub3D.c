/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenlahb <abenlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:30:17 by abenlahb          #+#    #+#             */
/*   Updated: 2023/08/28 12:30:17 by abenlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

void error_message(char *str, int fd)
{
    ft_putstr_fd(str, fd);
    exit(1);
}

int handle_arg(char *str)
{
    if (test_is_derctory(str))
        error_message("Error: invalid\n", 2);
    if (test_extension(str, "cub"))
        return (1);

    else if (!test_extension(str, "cub"))
        error_message("Error: invalid file extension\n", 2);
}
void initial_data(t_my_map *data_map)
{
    data_map->map = NULL;
    data_map->map_2=NULL;
    data_map->nb_line = 0;
}

void check_color(char **map)
{
    int found_f = 0;
    int found_c = 0;
    int i = 0;

    while (map[i])
    {
        while (isspace(*map[i]))
        {
            map[i]++;
        }

        if (ft_strncmp(map[i], "F ", 2) == 0)
        {
            found_f = 1;
        }
        else if (ft_strncmp(map[i], "C ", 2) == 0)
        {
            found_c = 1;
        }

        i++;
    }
    if (found_c + found_f != 2 || !found_c || !found_f)
    {
        error_message("Color problem", 2);
    }
}
void let_check(char **map) {
    int i = 0;
    int tex_numb = 0;
    int tex_flags[4] = {0};
    int found_f = 0;
    int found_c = 0;

    while (map[i]) {
      
        char *temp = map[i];

        while (isspace(*temp)) {
            temp++;
        }

        if (temp[0] == 'N' || temp[0] == 'S' || temp[0] == 'W' || temp[0] == 'E') {
            if (ft_strncmp(temp, "NO ", 3) == 0 ||
                ft_strncmp(temp, "SO ", 3) == 0 ||
                ft_strncmp(temp, "WE ", 3) == 0 ||
                ft_strncmp(temp, "EA ", 3) == 0) {

                if (ft_strncmp(temp, "NO ", 3) == 0) {
                    tex_flags[0]++;
                } else if (ft_strncmp(temp, "SO ", 3) == 0) {
                    tex_flags[1]++;
                } else if (ft_strncmp(temp, "WE ", 3) == 0) {
                    tex_flags[2]++;
                } else if (ft_strncmp(temp, "EA ", 3) == 0) {
                    tex_flags[3]++;
                }

                tex_numb++;
            }
        } else if (temp[0] == 'F' || temp[0] == 'C') {
            if (temp[1] == ' ') {
                if (temp[0] == 'F') {
                    found_f = 1;
                } else {
                    found_c = 1;
                }
            }
        }

        i++;
    }

    if (tex_numb != 4) {
        error_message("There must be exactly 4 textures\n", 2);
    }

    if (found_c + found_f != 2 || !found_c || !found_f) {
        error_message("Color problem", 2);
    }

    int j = 0;
    while (j < 4) {
        if (tex_flags[j] != 1) {
            error_message("just one \n", 2);
        }
        j++;
    }
}



void process_texture(t_my_map *param, char **splited)
{
    if (!splited[0])
        return;
    if (ft_strcmp(splited[0], NORTH_TEXTURE) == 0)
    {
        param->north_texture = ft_strdup(splited[1]);
    }

    else if (ft_strcmp(splited[0], SOUTH_TEXTURE) == 0)
        param->south_texture = ft_strdup(splited[1]);
    else if (ft_strcmp(splited[0], EAST_TEXTURE) == 0)
        param->east_texture = ft_strdup(splited[1]);
    else if (ft_strcmp(splited[0], WEST_TEXTURE) == 0)
        param->west_texture = ft_strdup(splited[1]);
}


int is_valid_digit(const char *str)
{
    
    int i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
        {
            return 0; 
        }
        i++;
    }
    return 1; 
}
int nbr_rgb(char **color)
{
    int i =0;
    while (color[i])
    {
        i++;
    }
    if(i != 3)
        return (1);
    return(0);
    
}
int get_rgb(char **str, t_color *color)
{
  int i =0;
  while (str[i])
  {
    
    i++;
  }
  if(i !=3 || ft_strlen(str[0]) >3 || ft_strlen(str[1]) >3 || ft_strlen(str[2]) > 3)
    return (1);

    if (!is_valid_digit(str[0]) || !is_valid_digit(str[1]) || !is_valid_digit(str[2]))
    {
        return 1;
    }

    int r = ft_atoi(str[0]);
    int g = ft_atoi(str[1]);
    int b = ft_atoi(str[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        return 1;
    }

    color->r = r;
    color->g = g;
    color->b = b;
    return 0; 
}
void procces_color(t_my_map *param, char **splited)
{

    if (!splited[0])
        return;

    if (!ft_strcmp(splited[0], F_COLOR))
    {
        if (get_rgb(splited + 1, &param->f_color) != 0)
        {
            error_message("invalid color ",2);
        }
    }

    else if (!ft_strcmp(splited[0], C_COLOR))
    {
  if (get_rgb(splited + 1, &param->c_color) != 0)
        {
            error_message("invalid color range\n",2);
        }
    }
       
}

void get_texture(t_my_map *param)
{
    int i = 0;
    char **splited;
    while (param->map[i])
    {
        splited = ft_split_str(param->map[i]);
        process_texture(param, splited);
        procces_color(param, splited);
        i++;
    }
    // here i have to freee
    free_2p(splited);

    if (!test_extension_xpm(param->north_texture + 1, "xpm") || !test_extension_xpm(param->south_texture + 1, "xpm") || !test_extension_xpm(param->east_texture + 1, "xpm") || !test_extension_xpm(param->west_texture + 1, "xpm"))
    {
        error_message("Texture filenames must have .xpm extension!\n", 2);
    }
    //    printf("=>%s\n",param->east_texture);
    //     const char *filename =param->east_texture;
    //     printf("%d\n",ft_strcmp(filename,"./textures/EA.xpm"));
    //     int fileDescriptor = open(filename, O_RDONLY);

    //     if (fileDescriptor == -1) {
    //         printf("File does not exist.\n");
    //     } else {
    //         printf("File exists.\n");
    //         close(fileDescriptor);
    //     }
    //     exit(0);

    if (open(param->north_texture, O_RDONLY) < 0 || open(param->south_texture, O_RDONLY) < 0 || open(param->east_texture, O_RDONLY) < 0 || open(param->west_texture, O_RDONLY) < 0)
    {
        error_message("Texture open probleme\n", 2);
    }
}


void start_parse(char *filename, t_my_map *src)
{
    int nbr_li;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        error_message("file open error\n", 2);
    }
    else if (is_empty(fd))
    {
        error_message("Your file is empty\n", 2);
    }
    else
    {
        initial_data(src);
        src->map = get_content(fd, src);
        let_dup(src, filename);
        let_check(src->map);
       
      
        get_texture(src);
        get_map(src);
        check_map(src);
        check2_map(src);
    }
    //  close(fd);
}

int main(int ac, char **av)
{

    t_my_map src;
    if (ac == 2)
    {
        if (handle_arg(av[1]))
        {
            start_parse(av[1], &src);
            raycasting(&src);
        }
    }
    else
    {
        error_message("args problem\n", 2);
    }

    return 0;
}