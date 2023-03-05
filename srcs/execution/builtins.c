/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:56:21 by nradal            #+#    #+#             */
/*   Updated: 2023/03/05 12:02:41 by nradal           ###   ########.fr       */
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
		return (ft_pwd(&data->cmd[i]));
	else if (which_builtins == 3)
		return (ft_export(&data->cmd[i], data->env));
	else if (which_builtins == 4)
		return (ft_unset(&data->cmd[i], data->env));
	else if (which_builtins == 5)
		return (ft_env(data->env, &data->cmd[i]));
	else if (which_builtins == 6)
	{
		if (data->size_cmd_array == 1 && ft_exit(data->cmd[i].args) == 0)
		{
			//free_data(data);
			exit_shell();
		}
	}
	return (1);
}

int builtins_handler(t_data *data, int i)
{
	if (data->size_cmd_array > 1)
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
			// ft_putendl_fd("Builtins, :", 2);
			// ft_putnbr_fd(data->cmd[i].fd_in, 2);
			// ft_putnbr_fd(data->cmd[i].fd_out, 2);
			// ft_putendl_fd("", 2);
			if (!builtins_launcher(data, i))
			{
				ft_putendl_fd("Rachele: builtins: something went wrong", 2);
				exit(EXIT_FAILURE);
			}
			exit (EXIT_SUCCESS);
		}
		else
		{
			;
			// if (waitpid(data->cmd[i].pid, &g_exit_code, 0) == -1)
			// {
			// 	ft_putendl_fd("waitpid", 2);
			// 	return (0);
			// }
			// g_exit_code %= 255;
		}
		return (1);
	}
	else
	{
		if (!builtins_launcher(data, i))
			return (0);
		return (1);
	}
}

char	**init_builtins_tab(void)
{
	char **builtins;
	
	builtins = malloc(7 * sizeof(char *));
	if (!builtins)
		return (NULL);
	builtins[0] = strdup("echo");
	builtins[1] = strdup("cd");
	builtins[2] = strdup("pwd");
	builtins[3] = strdup("export");
	builtins[4] = strdup("unset");
	builtins[5] = strdup("env");
	builtins[6] = strdup("exit");
	if (!builtins[0] || !builtins[1] || !builtins[2] || !builtins[3]
	    || !builtins[4] || !builtins[5] || !builtins[6])
	{
		free_strs(builtins);
		return (NULL);
	}
	return (builtins);
}

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (-2);
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
