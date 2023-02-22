/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:08:48 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 16:59:35 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **args)
{
	int	code;

	if (args[0])
	{
		if (args[1])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		else if (!is_exit_arg_valid(args[0]))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (1);
		}
		g_exit_code = get_exit_code(args[0]);
	}
	return (0);
}

int	get_exit_code(char *arg)
{
	int				code;
	unsigned char	uc;

	code = overflow_atoi(arg);
	uc = (unsigned char)code;
	code = (int)uc;
	return (code);
}

int	overflow_atoi(const char *str)
{
	int		sign;
	long	r;

	r = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		r = r * 10 + *str - '0';
		str++;
	}
	return ((int)r * sign);
}

int	is_exit_arg_valid(char *arg)
{
	int	i;

	if (!arg)
		return (1);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_shell(void)
{
	ft_putendl_fd("exit", 1);
	ft_putnbr_fd(g_exit_code, 2);
	exit(g_exit_code);
}
