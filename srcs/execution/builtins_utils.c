/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:46:38 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 05:35:34 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_builtins_handler(t_cmd_array *cmd, char *arg)
{
	ft_putstr_fd("Rachele: ", 2);
	ft_putstr_fd(cmd->the_cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	if (ft_strcmp(cmd->the_cmd, "env") == 0)
		ft_putstr_fd(": illegal argument\n", 2);
	else
	{
		ft_putstr_fd(": invalid option\n", 2);
	}
}

bool	option_checker(char **args)
{
	if (args && args[0])
	{
		if (ft_strncmp(args[0], "-", 1) == 0)
			return (false);
	}
	return (true);
}

bool	builtin_option_checker(int cmd_id, char **args)
{
	if (cmd_id == 0 || cmd_id == 1 || cmd_id == 6)
		return (true);
	else if (cmd_id == 2 || cmd_id == 3 || cmd_id == 4)
		return (option_checker(args));
	else
		if (args == NULL || args[0] == NULL)
			return (true);
	return (false);
}
