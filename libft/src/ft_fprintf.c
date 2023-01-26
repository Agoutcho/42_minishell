/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:07:13 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/26 23:10:24 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fprintf.h"

static int	ft_is_ok(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	else
		return (0);
}

void	ft_fputchar_printf(char c, int *r, int fd)
{
	write(fd, &c, 1);
	*r += 1;
}

static void	ft_fputstr(char *c, int *r, int fd)
{
	while (*c)
	{
		write(fd, c, 1);
		*r += 1;
		c++;
	}
}

static void	ft_fprint_it(const char s, va_list p, int *r, int fd)
{
	static void	(*f_int[9])(int, int *, int) = {NULL, NULL,
		ft_fputnbr_printf, NULL, ft_fputhexa_up, NULL, NULL,
		ft_fputnbr_printf, ft_fputhexa_low};
	void		*temp;

	if (!(s == '%'))
		temp = va_arg(p, void *);
	if (s == '%')
		ft_fputchar_printf('%', r, fd);
	else if (s % 14 == 1)
		ft_fputchar_printf((char)temp, r, fd);
	else if (s % 14 == 3 && temp != NULL)
		ft_fputstr((char *)temp, r, fd);
	else if (s % 14 == 3 && temp == NULL)
		ft_fputstr("(null)", r, fd);
	else if (s % 14 == 5)
		ft_fputnbr_u((unsigned int)temp, r, fd);
	else if (s % 14 > 1 && s % 14 < 9)
		f_int[s % 14]((int)temp, r, fd);
	else if (s % 14 == 0)
	{
		ft_fputstr("0x", r, fd);
		ft_fputadr((unsigned long)temp, r, fd);
	}
}

int	ft_fprintf(int fd, const char *s, ...)
{
	int		result;
	va_list	ptr;

	va_start(ptr, s);
	result = 0;
	while (*s)
	{
		if (!(*s == '%'))
			ft_fputchar_printf(*(char *)s, &result, fd);
		else if (*s++ == '%' && ft_is_ok(*s--))
			ft_fprint_it(*++s, ptr, &result, fd);
		s++;
	}
	va_end(ptr);
	return (result);
}
