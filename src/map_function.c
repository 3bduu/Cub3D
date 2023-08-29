#include "../include/cub3D.h"

int	is_char_pattern(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

void get_postion(t_my_map *src)
{
    int i = 0;
    int j;
   
    while (src->map_2[i])
    {
        
        j = 0;
        while (src->map_2[i][j])
        {

            if (is_char_pattern(src->map_2[i][j], "NSEW"))
            {
                src->row_player = i;
                src->col_player = j;
                src->pos_player = src->map_2[i][j];
                return;
            }
            j++;
        }
        i++;
    }
    error_message("have set pos player\n", 2);
}
int	check_space(char **map, int row, int col)
{
   if(map[row+1] !=NULL)
   {
if (map[row][col + 1] == ' ' || map[row][col - 1] == ' '
		|| map[row + 1][col] == ' ' || map[row - 1][col] == ' ')
		error_message("invalid map\n",2);
     }

    
	
    return (0);
	
}

void check_map(t_my_map *src)
{
    int i;
    int j;
    int flag;

    i =0;
    flag=0;
  
    while (src->map_2[i])
    {
        j = 0;
        while (src->map_2[i][j])
        {
            
            if (!is_char_pattern(src->map_2[i][j], "NSEW01 "))
                error_message("must have this NSEW01\n", 2);
          //  printf("==>%c\n",src->map_2[i][j]);
            if(is_char_pattern(src->map_2[i][j], "NSEW") && !check_space(src->map_2,i,j) )
            {
             
                flag++;
            }
               
            
            j++; 
        }
        i++;
    }
    if(flag >1)
        error_message("have at lest one player pos\n",2);
    
}

int count_soulton_lines(char **map, int map_height)
{
    int soulton_count = 0;
    int i = 0;

    while (i < map_height)
    {
        char *line = ft_strtrim(map[i],"\n\r");
        
    
    
        int len = ft_strlen(line);
        int j = 0;
        int is_valid_line = 1;
        int has_valid_character = 0;

        while (j < len)
        {
            char c = line[j];
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
            {
                is_valid_line = 0;
                break;
            }
            if (c != ' ' && c != '\t')
            {
                has_valid_character = 1;
            }
            j++;
        }

        if (is_valid_line && has_valid_character)
        {
            soulton_count++;
        }

        i++;
    }

    return soulton_count;
}
void get_map(t_my_map *src)
{
    int get_len = count_soulton_lines(src->map, src->nb_line)+1;
   src->nb_map2=get_len;

    src->map_2 = malloc(sizeof(char *) * (get_len + 1));
    int start = src->nb_line - get_len+1;
    
    if (!src->map[start])
        error_message("1 invalid map\n", 2);
    if (count_soulton_lines(src->map, src->nb_line) == 0)
        error_message("2 invalid map\n", 2);
    int j = 0;
   
    while (src->map[start])
    {
       
        src->map_2[j] = ft_str_n_dup(src->map[start], ft_strlen(ft_strtrim(src->map[start], "\n\r")));
        if (is_videe(src->map_2[j]))
        {

            error_message(" 3 invalid map\n", 2);
        }

        start++;
        j++;
    }
    src->map_2[j] = NULL;
src->biger_row = count_longest_line(src->map_2);

 j =0;
 while (src->map_2[j])
 {
   src->map_2[j]=ft_strlen_dup(src->map_2[j],src->biger_row);
    j++;
 }
 src->map_2[j] = NULL;
 
  
 
    get_postion(src);
}