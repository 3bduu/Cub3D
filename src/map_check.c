#include "../include/cub3D.h"


char **set_a(char **dup)
{
    int i =0;
    int j;
    while (dup[i])
    {
        j =0;
        while (dup[i][j])
        {
            if(dup[i][j]==' ')
                dup[i][j]='A';
            j++;
        }
        i++;
    }
    
    return dup;

}
void check_souranded(char **dub)
{
    int i =0;
    int j;
    
    while (dub[i])
    {
        j= 0;
      
      
        while (dub[i][j])
        {
            if(dub[i][j]=='A')
            {
                   if ((dub[i][j + 1] && !is_char_pattern(dub[i][j + 1], "A1"))
					|| dub[i + 1] && !is_char_pattern(dub[i + 1][j], "A1"))
                    {
                        error_message("invalid map hnaaa\n",2);
                    }
					
				if ((j != 0 && !is_char_pattern(dub[i][j - 1], "A1"))
					|| (i != 0 && !is_char_pattern(dub[i - 1][j], "A1")))
					error_message("invalid map ajiiii\n",2);
            }
        
            j++;
        }
        
        i++;
    }
       free_2p(dub);
}
void check2_map(t_my_map *src)
{
    int j = 1;
    char **dub;
    int i = 0;
  
    
    dub = malloc(sizeof(char *) * (src->nb_map2 + 3));
    dub[0] = malloc(src->biger_row + 3);
    ft_memset(dub[0], 'A', src->biger_row+2);
    dub[0][src->biger_row+2] = '\0';

    while (i < src->nb_map2) {
        int row_length = ft_strlen(src->map_2[i]);
        
       
        dub[j] = malloc(row_length + 3);
        dub[j][0] = 'A';
        ft_strcpy(dub[j] + 1, src->map_2[i]);
        dub[j][row_length + 1] = 'A';
        dub[j][row_length + 2] = '\0';
        
        i++;
        j++;
    }

    dub[j] = malloc(src->biger_row + 3); 
    ft_memset(dub[j], 'A', src->biger_row+2);
    dub[j][src->biger_row+2] = '\0';
    j++;
    
    dub[j] = NULL;

    dub=set_a(dub);
    check_souranded(dub);
 
    

}