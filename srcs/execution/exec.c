/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:50 by nradal            #+#    #+#             */
/*   Updated: 2023/03/08 23:49:12 by atchougo         ###   ########.fr       */
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
	signal(SIGINT, sig_int_handler_exec);
	signal(SIGQUIT, sig_quit_handler);
	init_cmd_fd(data);
	while (i < data->size_cmd_array)
	{
		if (!ft_create_pipe(data, i))
			return (0);
		is_bt = is_builtins(data->cmd[i].the_cmd);
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
				if (!redirections_handler(&data->cmd[i]))
				{
					big_free(data);
					exit (g_exit_code);
				}
				if (!ft_connect_pipe(&data->cmd[i]))
				{
					ft_putendl_fd("connect pipes", 2);
					return (0);
				}
				ft_close_child_fd(data, i);
				execute(data, i);
			}
		}
		if (!ft_close_pipe(&data->cmd[i]))
			return (ft_putendl_fd("close pipe", 2), 0);
		i++;
	}
	i = 0;
	while (i < data->size_cmd_array)
	{
		is_bt = is_builtins(data->cmd[i].the_cmd);
		if (is_bt == -1 || data->size_cmd_array > 1)
		{
			if (waitpid(data->cmd[i].pid, &g_exit_code, 0) == -1)
				return (ft_putendl_fd("Rachele: waitpid", 2), 0);
			// g_exit_code %= 255;
			if (WIFEXITED(g_exit_code))
				g_exit_code = WEXITSTATUS(g_exit_code);
			else if (WIFSIGNALED(g_exit_code))
				g_exit_code = 128 + WTERMSIG(g_exit_code);
		}
		i++;
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (reuncannon(&data->termio), 1);
}

void	execute(t_data *data, int i)
{
	int is_exec;

	if (!data->cmd[i].the_cmd)
		exit (EXIT_SUCCESS);
	is_exec = is_executable(data, i);
	if (is_exec == 1)
	{
		if (!executable_handler(data, i))
			exit (g_exit_code);
	}
	else if (is_exec == 0)
			commands_handler(data, i);
	exit (EXIT_SUCCESS);
}
