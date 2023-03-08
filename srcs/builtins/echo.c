/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:50:52 by nradal            #+#    #+#             */
/*   Updated: 2023/03/08 23:48:17 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_cmd_array *cmd)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	while (cmd->args && cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
	{
		option = true;
		i++;
	}
	while (cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		if (cmd->args[i + 1] != NULL)
			ft_putchar_fd(' ', cmd->fd_out);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', cmd->fd_out);
	return (set_g_exit_code(0, 1));
}
