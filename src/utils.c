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


int test_extension(char *file_name, char *extension) {
    char *last_period;
    last_period = ft_strrchr(file_name, '.');
    if (last_period == NULL)
        return (0);
    if(extension=="xpm")
    {
        char **splited=ft_split(last_period+1,' ');
       // printf("spltes==> %s",splited[0]);
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
int count_longest_line(char **map) {
    int max_length = 0;
    int i = 0;

    while (map[i] != NULL) {
        
        int length = ft_strlen(map[i]);
       
        if (length > max_length) {
            max_length = length;
        }
        i++;
    }

    return max_length;
}

int	check_new_line(char *str)
{
	return (str[ft_strlen(str) - 1] == '\n');
}
char	*ft_str_n_dup(const char *s1, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s1)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}



char *ft_strlen_dup(const char *s1, size_t len) {
    char *ptr;
    size_t i;

    if (!s1)
        return NULL;

    ptr = (char *)malloc(sizeof(char) * (len + 1));
    if (!ptr)
        return NULL;

    i = 0;
    while (i < len && s1[i] != '\0') {
        ptr[i] = s1[i];
        i++;
    }

    // Fill the remaining space with spaces
    while (i < len) {
        ptr[i] = ' ';
        i++;
    }

    ptr[i] = '\0';
    return ptr;
}

int	is_videe(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!isspace(s[i]))
			return (0);
	return (1);
}

int isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
char *ft_strcpy(char *dest,  char *src) {
    char *original_dest = dest;  
    
   
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    
    *dest = '\0'; 
    
    return original_dest;
}
