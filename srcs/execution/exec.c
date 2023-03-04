/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:50 by nradal            #+#    #+#             */
/*   Updated: 2023/03/04 15:47:21 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_cmd_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size_cmd_array)
	{
		data->cmd[i].fd_in = STDIN_FILENO;
		data->cmd[i].fd_out = STDOUT_FILENO;
		i++;
	}
}

int	execution(t_data *data)
{
	int	i;
	int is_bt;

	i = 0;
	rerestore(&data->termio);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler_exec);
	init_cmd_fd(data);
	while (i < data->size_cmd_array)
	{
		if (!ft_create_pipe(data, i))
			return (0);
		is_bt = is_builtins(data->cmd[i].the_cmd);
		if (is_bt == -2)
			return (0);
		if (is_bt >= 0)
		{
			if (!builtins_handler(data, i))
			{
				ft_putendl_fd("builtins_handler", 2);
				return (0);
			}
		}
		else
		{
			data->cmd[i].pid = fork();
			if (data->cmd[i].pid == -1)
			{
				perror("Rachele: fork");
				return (0);
			}
			else if (data->cmd[i].pid == 0)
			{	
				if (!ft_connect_pipe(&data->cmd[i]))
				{
					ft_putendl_fd("connect pipes", 2);
					return (0);
				}
				ft_close_child_fd(data, i);
				if (!execute(data, i))
				{
					ft_putendl_fd("execute", 2);
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
		if (is_bt < 0)
		{
			if (waitpid(data->cmd[i].pid, &g_exit_code, 0) == -1)
			{
				ft_putendl_fd("waitpid", 2);
				return (0);
			}
			g_exit_code %= 255;
		}
		if (!ft_close_pipe(&data->cmd[i]))
		{
			ft_putendl_fd("close pipe", 2);
			return (0);
		}
		i++;
	}
	return (reuncannon(&data->termio), 1);
}

int	execute(t_data *data, int i)
{
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
