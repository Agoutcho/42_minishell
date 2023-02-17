/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:07:58 by nradal            #+#    #+#             */
/*   Updated: 2021/11/22 11:15:02 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	char	*rtn;

	rtn = (char *)haystack;
	i = 0;
	j = 0;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (haystack[i])
	{
		while (haystack[i] == needle[j] && n > i)
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return (rtn + i - j);
		}
		i -= j - 1;
		j = 0;
	}
	return (NULL);
}
