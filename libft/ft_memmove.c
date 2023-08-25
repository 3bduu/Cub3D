/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:34:17 by mballa            #+#    #+#             */
/*   Updated: 2023/03/22 21:11:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*sr;

	d = (unsigned char *) dst;
	sr = (unsigned char *) src;
	
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
		ft_memcpy(d, src, len);
	else
	{
		while (len-- > 0)
			d[len] = sr[len];
	}
	return (dst);
}