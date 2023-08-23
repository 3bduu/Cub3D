#include "../include/cub3D.h"

int is_spacee(char c)
{
    if(c>=9 && c <=33)
        return (1);
    return (0);
}
void	free_2p(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}