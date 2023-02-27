/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:53:59 by noah              #+#    #+#             */
/*   Updated: 2023/02/27 03:34:54 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + 1;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s1, size);
	return (str);
}
