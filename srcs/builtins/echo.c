/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:50:52 by nradal            #+#    #+#             */
/*   Updated: 2023/03/13 15:36:20 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_valid_arg(char *arg);

int	ft_echo(t_cmd_array *cmd)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	while (cmd->args && cmd->args[i] && echo_valid_arg(cmd->args[i]))
	{
		option = true;
		i++;
	}
	while (cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (set_g_exit_code(0, 1));
}

int	echo_valid_arg(char *arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}
