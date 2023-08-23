#include "../include/cub3D.h"

void error_message(char *str,int fd)
{
   ft_putstr_fd(str,fd);
    exit(1);
}


int test_extension(char *file_name, char *extension) {
    char *last_period;
    last_period = ft_strrchr(file_name, '.');
    if (last_period == NULL)
        return (0);
    if(extension=="xpm")
    {
        char **splited=ft_split(last_period+1,' ');
        printf("spltes==> %s",splited[0]);
    }
    if (ft_strcmp(last_period + 1, extension) == 0) {
        
        return (1);
    } else {
       
        return (0);
    }
}

int test_extension_xpm(char *file_name, char *extension) {
    char *last_period;
    last_period = ft_strrchr(file_name, '.');
    

  
    if (last_period == NULL)
        return (0);
 
    if (ft_strcmp(last_period+1, extension) == 0) {
      
        return (1);
    } else {
    
        return (0);
    }
}

int is_empty(int fd) {
    char *line;
    int isFileEmpty = 1;

    line = get_next_line(fd);
    while (line) {
        if (*line != '\0') 
        { 
            isFileEmpty = 0;
            break;
        }
        free(line);
        line = get_next_line(fd);
    }

    return isFileEmpty;
}
int test_is_derctory(char *file_name)
{
    int fd;
    fd=open(file_name,O_DIRECTORY);
    if (fd != -1)
        return (1);
    return (0);

}
int handle_arg(char *str)
{
    if(test_is_derctory(str))   
         error_message("Error: invalid\n",2);
    if(test_extension(str,"cub"))
        return (1);

    else if(!test_extension(str,"cub"))
     error_message("Error: invalid file extension\n",2);
        
}
void initial_data(t_my_map *data_map)
{
    data_map->map = NULL;
    data_map->nb_line = 0;
}

int isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' );
}
int check_color(int *index, char **map) {
    int found_f = 0;
    int found_c = 0;   
    while (map[*index] &&  isspace(map[*index][0]))
    {
 
    (*index)++;
    }
       
    int i = *index;
    int j = i + 2;

    while (i < j && map[i]) {
        if(map[i][0] == '\0' || isspace(map[i][0])) 
            i++;
        if (is_spacee(*map[i])) {
            map[i]++;
        }
        
        if (ft_strncmp(map[i], "F ", 2) == 0) {
            found_f = 1;
        } else if (ft_strncmp(map[i], "C ", 2) == 0) {
            found_c = 1;
        }

        i++;
    }
    if(found_c+found_f !=2 || !found_c || !found_f)
    {
         error_message("Color problem", 2);
    }
    return (i);
}


int  let_check(char **map)
{
  int i =0;
  int nb_conten;
  int nb_line;
  nb_line=0;
  int tex_numb;
  tex_numb=0;
  //check texteurs 
  ///skip space
 
 
while (i < 4 && map[i])
{
    if(is_spacee(*map[i]))
        map[i]++;
   if (ft_strncmp(map[i], "NO ", 3) == 0
			|| ft_strncmp(map[i], "SO ", 3) == 0
			|| ft_strncmp(map[i], "WE ", 3) == 0
			|| ft_strncmp(map[i], "EA ", 3) == 0)
            {
                tex_numb++;
            }
    
    i++;
}

if( i !=tex_numb && tex_numb !=4)
     error_message("texures probleme\n",2);
nb_line=check_color(&i,map);
return (nb_line);
}

void get_map(t_my_map *src,int nbr_li)
{
  
src->nb_raw=src->nb_line-nbr_li;
printf("==>%d\n",src->nb_raw);
    
}
void process_texture(t_my_map *param, char **splited) {
    if (!splited[0])
        return;
    if (ft_strcmp(splited[0], NORTH_TEXTURE) == 0  )
    {
      param->north_texture = ft_strdup(splited[1]);
    
    }
       
    else if (ft_strcmp(splited[0], SOUTH_TEXTURE) == 0 )
        param->south_texture = ft_strdup(splited[1]);
    else if (ft_strcmp(splited[0], EAST_TEXTURE) == 0  )
        param->east_texture = ft_strdup(splited[1]);
    else if (ft_strcmp(splited[0], WEST_TEXTURE) == 0 )
        param->west_texture = ft_strdup(splited[1]);
  
}

void get_texture(t_my_map *param) {
    int i = 0;
    char **splited;
    while (i < 4) {
        splited = ft_split_str(param->map[i++]);
        process_texture(param, splited);
    }
    //here i have to freee
    free_2p(splited);

 
      if (!test_extension_xpm(param->north_texture+1,"xpm")
        || !test_extension_xpm(param->south_texture+1,"xpm")
        || !test_extension_xpm(param->east_texture+1,"xpm")
        || !test_extension_xpm(param->west_texture+1,"xpm")) {
      error_message("Texture filenames must have .xpm extension!\n",2);
       
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

    if (open(param->north_texture, O_RDONLY) < 0
		|| open(param->south_texture, O_RDONLY) < 0
		|| open(param->east_texture, O_RDONLY) < 0
		|| open(param->west_texture, O_RDONLY) < 0)
        {
    error_message("Texture open probleme\n",2);
        }
		
    
}
void start_parse( char *filename, t_my_map *src) {
    int nbr_li;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        error_message("file open error\n", 2);
    } else if (is_empty(fd)) {
        error_message("Your file is empty\n", 2);
    } else {
        initial_data(src);
        src->map = get_content(fd, src);
        let_dup(src, filename);
        nbr_li=let_check(src->map);
        //let get textaure
        get_texture(src);
      //get_map(src,nbr_li);
    }
  //  close(fd);
}

int main(int ac, char **av) {
   
    t_my_map src;
    if (ac == 2) {
        if (handle_arg(av[1])) {
            start_parse(av[1], &src);
            raycasting(&src);
        }
    } else {
        error_message("args problem\n", 2);
    }
    

    return 0;
}