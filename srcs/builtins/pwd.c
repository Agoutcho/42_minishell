/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:40:08 by nradal            #+#    #+#             */
/*   Updated: 2023/03/09 18:17:20 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_env_pwd(t_cmd_array *cmd, t_env *env)
{
	t_env	*temp;
	temp = search_key("PWD=", env);
	if (temp)
	{
		ft_putendl_fd(temp->value, cmd->fd_out);
		g_exit_code = 0;
	}
	else
	{
		ft_putendl_fd("Rachele : pwd: no pwd set", cmd->fd_out);
		g_exit_code = 1;
	}
	env = env->first;
}

int	ft_pwd(t_cmd_array *cmd, t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_env_pwd(cmd, env);
		return (1);
	}
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (set_g_exit_code(0, 1));
}