/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:15:14 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/26 23:10:27 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fprintf.h"

void	ft_fputhexa_up(int n, int *r, int fd)
{
	char			*hexa;
	unsigned int	number;

	number = (unsigned int)n;
	hexa = "0123456789ABCDEF";
	if (number > 15)
		ft_fputhexa_up((number / 16), r, fd);
	ft_fputchar_printf(hexa[number % 16], r, fd);
}

void	ft_fputhexa_low(int n, int *r, int fd)
{
	char			*hexa;
	unsigned int	number;

	number = (unsigned int)n;
	hexa = "0123456789abcdef";
	if (number > 15)
		ft_fputhexa_low((number / 16), r, fd);
	ft_fputchar_printf(hexa[number % 16], r, fd);
}

void	ft_fputnbr_u(unsigned int n, int *r, int fd)
{
	char			*decimal;
	unsigned int	number;

	number = n;
	decimal = "0123456789";
	if (number > 9)
		ft_fputnbr_u((number / 10), r, fd);
	ft_fputchar_printf(decimal[number % 10], r, fd);
}

void	ft_fputadr(unsigned long p, int *r, int fd)
{
	unsigned long	nb;
	char			*hexa;

	nb = p;
	hexa = "0123456789abcdef";
	if (nb > 15)
		ft_fputadr((nb / 16), r, fd);
	ft_fputchar_printf(hexa[nb % 16], r, fd);
}

void	ft_fputnbr_printf(int n, int *r, int fd)
{
	char	*decimal;
	long	number;

	number = (long)n;
	decimal = "0123456789";
	if (number < 0)
	{
		number = -number;
		ft_fputchar_printf('-', r, fd);
	}
	if (number > 9)
		ft_fputnbr_printf((number / 10), r, fd);
	ft_fputchar_printf(decimal[number % 10], r, fd);
}
