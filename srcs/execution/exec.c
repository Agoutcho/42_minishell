/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:50 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 05:19:31 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execution(t_data *data)
{
	int	i;

	i = 0;
	// while (data->cmd[i].the_cmd != NULL)
	while (i < data->size_cmd_array)
	{
		if (!pipe_handler(data, i))
		{
			return (0);
		}
		if (redirections_handler(&data->cmd[i]))
		{
			if (!execute(data, i))
				return (0);
		}
		if (!redirections_closer(&data->cmd[i], data->fd_saver))
		{
			return (0);
		}
		if (!pipe_closer(data, i))
		{
			return (0);
		}
		i++;
	}
}

int	execute(t_data *data, int i)
{
	int	is_bt;

	is_bt = is_builtins(data->cmd[i].the_cmd);
	if (is_bt == -2)
		return (0);
	if (is_bt >= 0)
	{
		if (builtin_option_checker(is_bt, data->cmd[i].args))
		{
			if (builtins_handler(data, i) == 0)
				return (0);
		}
		else
		{
			error_builtins_handler(&data->cmd[i]);
			return (1);
		}
	}
	else if (is_executable(data->cmd[i].the_cmd) == true)
	{
		if (!executable_handler(&data->cmd[i], data->env))
			return (0);
	}
	else if (!commands_handler(&data->cmd[i], data->env))
		return (0);
}
