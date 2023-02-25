/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:53:59 by noah              #+#    #+#             */
/*   Updated: 2021/11/16 13:03:21 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s1) + 1;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s1, size);
	return (str);
}
