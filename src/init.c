#include "../include/cub3D.h"


char **get_content(int fd, t_my_map *info_map) {
    
    char *line;
    int i = 0;

    line = get_next_line(fd);
    while (line) {
        info_map->nb_line++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
   info_map->map = malloc(sizeof(char *) * (info_map->nb_line +1));
    if (!info_map->map) {
        error_message("alloc problem\n", 2);
    }
    close(fd);
    return info_map->map;
}

void let_dup(t_my_map *info_mapm, char *file_name) {
    int i = 0;
    int fd = open(file_name, O_RDONLY);
    char *line;
    line = get_next_line(fd);
    
    while (line) {
        info_mapm->map[i] = ft_strdup(line);
        free(line);
        i++;
        line = get_next_line(fd);
    }
    
    info_mapm->map[i] = NULL;

}

