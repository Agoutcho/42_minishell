/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:56:21 by nradal            #+#    #+#             */
/*   Updated: 2023/02/18 13:21:57 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_handler(t_data *data, int i)
{
	int	which_builtins;

	which_builtins = is_builtins(data->cmd[i].the_cmd);
	if (which_builtins == 0)
		return (ft_echo(data->cmd[i].args));
	else if (which_builtins == 1)
		return (ft_cd(&data->cmd[i], data->env));
	else if (which_builtins == 2)
		return (ft_pwd(data->cmd[i].args));
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
			free_data(data);
			exit_shell();
		}
	}
	return (1);
}

char	**init_builtins_tab(char **builtins)
{
	builtins = malloc(6 * sizeof(builtins));
	if (!builtins)
		return (NULL);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	return (builtins);
}

int	is_builtins(char *cmd)
{
	int		i;
	char	**builtins;

	builtins = init_builtins_tab(builtins);
	if (!builtins)
		return (-2);
	i = 0;
	while (i <= 6)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
		{
			free(builtins);
			return (i);
		}
		i++;
	}
	return (-1);
}
