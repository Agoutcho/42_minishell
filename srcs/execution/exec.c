/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:50 by nradal            #+#    #+#             */
/*   Updated: 2023/02/28 19:37:10 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execution(t_data *data)
{
	int	i;
	int is_bt;

	i = 0;
	rerestore(&data->termio);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler_exec);
	while (i < data->size_cmd_array)
	{
		// create pipe
		is_bt = is_builtins(data->cmd[i].the_cmd);
		if (is_bt == -2)
			return (0);
		else if (is_bt >= 0)
		{
			// if (!pipe_handler(data, i))
			// 	return (0);
			if (builtin_option_checker(is_bt, data->cmd[i].args))
			{
				if (redirections_handler(&data->cmd[i]))
				{
					if (builtins_handler(data, i) == 0)
						return (0);
					if (!redirections_closer(&data->cmd[i], data->fd_saver))
						return (0);
				}
				// if (!pipe_closer(data, i))
				// 	return (0);
			}
			else
			{
				error_builtins_handler(&data->cmd[i], data->cmd[i].args[0]);
				return (0);
			}
		}
		else
		{
			// pipe
			data->cmd[i].pid = fork();
			if (data->cmd[i].pid == -1)
				return (0);
			else if (data->cmd[i].pid == 0)
			{
				// if (!pipe_handler(data, i))
				// 	return (0);
				if (redirections_handler(&data->cmd[i]))
				{
					if (!execute(data, i))
						return (0);
				}
			}
		}
		i++;
	}
	i = 0;
	while (i < data->size_cmd_array)
	{
		is_bt = is_builtins(data->cmd[i].the_cmd);
		if (is_bt >= 0)
			i++;
		else
		{
			if (waitpid(data->cmd[i].pid, &g_exit_code, 0) == -1)
				return (0);
			g_exit_code %= 255;
			i++;
		}
	}
	return (reuncannon(&data->termio), 1);
}

int	execute(t_data *data, int i)
{
	int	is_bt;
	int is_exec;

	if (!data->cmd[i].the_cmd)
		return (1);
	is_exec = is_executable(data->cmd[i].the_cmd);
	if (is_exec == 1)
	{
		if (!executable_handler(&data->cmd[i], data->env))
			return (0);
	}
	else if (is_exec == 0)
		commands_handler(&data->cmd[i], data->env);
	return (1);
}
