/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:26:19 by nradal            #+#    #+#             */
/*   Updated: 2021/11/11 11:50:55 by nradal           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	destl;
	unsigned int	norm;

	i = -1;
	j = -1;
	destl = 0;
	while (++i < size && dest[i])
		destl++;
	if (i == size)
		return (i + (unsigned int)ft_strlen(src));
	while (src[++j])
	{
		norm = size - i - 1;
		if (j < norm)
		{
			dest[destl] = src[j];
			destl++;
		}
	}
	dest[destl] = '\0';
	return (i + j);
}
