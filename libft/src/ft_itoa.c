/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:38:54 by noah              #+#    #+#             */
/*   Updated: 2021/11/17 16:50:35 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_intlen(long long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*tab;
	int				len;
	int				is_negative;
	long long int	ln;

	is_negative = 0;
	ln = n;
	len = ft_intlen(ln);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	if (ln < 0)
	{
		ln *= -1;
		tab[0] = '-';
		is_negative = 1;
	}
	while (len > is_negative)
	{
		tab[--len] = (ln % 10) + '0';
		ln /= 10;
	}
	return (tab);
}
