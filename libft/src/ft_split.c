/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:02:56 by noah              #+#    #+#             */
/*   Updated: 2022/10/04 14:44:13 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_nbr_str(const char *str, char c)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (*str)
	{
		if (*str != c && b == 0)
		{
			b = 1;
			i++;
		}
		else if (*str == c)
			b = 0;
		str++;
	}
	return (i);
}

char	*ft_dup_str(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		ft_putendl_fd("error : malloc in libft/src/ft_split.c > ft_dup_str", 2);
		exit (1);
	}
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((ft_nbr_str(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = ft_dup_str(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
