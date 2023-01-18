/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:53:17 by noahrd0           #+#    #+#             */
/*   Updated: 2022/10/04 00:11:28 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcjoin(char *s1, char *s2, int c)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = 0;
	j = 0;
	while (s1[j])
		joined[i++] = s1[j++];
	joined[i++] = c;
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (joined);
}
