/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:50:52 by nradal            #+#    #+#             */
/*   Updated: 2023/02/27 00:02:57 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	while (args && args[i] && !ft_strcmp(args[i], "-n"))
	{
		option = true;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (set_g_exit_code(0, 1));
}
