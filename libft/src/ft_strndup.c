/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:18:36 by noahrd0           #+#    #+#             */
/*   Updated: 2022/10/04 00:10:47 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(char *str, unsigned int n)
{
	char			*dup;
	unsigned int	i;

	i = 0;
	dup = malloc(sizeof(char) * n + 1);
	if (!dup)
	{
		ft_putendl_fd("[>]	An error occured in ft_strndup", 2);
		free(dup);
		exit(1);
	}
	while (i < n)
		dup[i++] = *str++;
	dup[n] = '\0';
	return (dup);
}
