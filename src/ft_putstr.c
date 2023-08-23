
#include "../include/cub3D.h"

// void	ft_putchar(char c, int fd)
// {
// 	write (fd, &c, 1);
// }


// int	ftt_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

// char	*ft_strrchr(const char *s, char c)
// {
// 	int		lent;
// 	char	*str;

// 	lent = 0;
// 	str = (char *) s;
// 	while (str[lent])
// 		lent++;
// 	while (lent >= 0)
// 	{
// 		if (str[lent] == c)
// 			return ((char *) &str[lent]);
// 		lent--;
// 	}
// 	return (0);
// }

// int	ft_strncmp( char *s1,  char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	i = 0;
// 	if (n <= 0)
// 		return (0);
// 	while (i < n)
// 	{
// 		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
// 			return (str1[i] - str2[i]);
// 		i++;
// 	}
// 	return (0);
// }