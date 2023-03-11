/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:56:21 by nradal            #+#    #+#             */
/*   Updated: 2023/03/11 22:17:31 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_launcher(t_data *data, int i)
{
	int	which_builtins;

	which_builtins = is_builtins(data->cmd[i].the_cmd);
	if (which_builtins == 0)
		return (ft_echo(&data->cmd[i]));
	else if (which_builtins == 1)
		return (ft_cd(&data->cmd[i], data->env));
	else if (which_builtins == 2)
		return (ft_pwd(data->env));
	else if (which_builtins == 3)
		return (ft_export(&data->cmd[i], data->env));
	else if (which_builtins == 4)
		return (ft_unset(&data->cmd[i], data->env));
	else if (which_builtins == 5)
		return (ft_env(data->env));
	else if (which_builtins == 6)
	{
		if (data->size_cmd_array == 1 && ft_exit(data->cmd[i].args) == 0)
		{
			// TODO big free
			exit_shell();
		}
		else 
			ft_exit(data->cmd[i].args);		
	}
	return (1);
}

int	builtins_handler(t_data *data, int i)
{
	if (data->size_cmd_array > 1)
	{
		data->cmd[i].pid = fork();
		if (data->cmd[i].pid == -1)
			return (perror("Rachele: fork"), 0);
		else if (data->cmd[i].pid == 0)
		{
			if (!redirections_handler(&data->cmd[i]))
				free_exit(data, EXIT_FAILURE);
			if (!ft_connect_pipe(&data->cmd[i]))
			{
				ft_putendl_fd("connect pipes", 2);
				return (0);
			}
			ft_close_child_fd(data, i);
			if (!builtins_launcher(data, i))
			{
				ft_close_pipe(&data->cmd[i]);
				free_exit(data, g_exit_code);
			}
			free_exit(data, g_exit_code);
		}
		return (1);
	}
	else
	{
		if (!redirections_handler(&data->cmd[i]))
			return (ft_close_pipe(&data->cmd[i]), 1);
		if (!builtins_launcher(data, i))
			return (0);
		return (1);
	}
}

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "export") == 0)
		return (3);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (4);
	else if (ft_strcmp(cmd, "env") == 0)
		return (5);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (6);
	return (-1);
}
