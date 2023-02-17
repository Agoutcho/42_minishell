/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:38:58 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 16:00:02 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_cmd_array *cmd, t_env *env)
{
	if (cmd->args[1] != NULL)
	{
		ft_putendl_fd("cd: string not in pwd", 2);
		return (1);
	}
	else if (cmd->args[0][0] == '-' && cmd->args[0][1] == '\0')
		return (cd_oldpwd(cmd, env));
	else if (access(cmd->args[0], F_OK) == 0)
	{
		if (!change_pwd(env, "OLDPWD="))
			return (0);
		if (chdir(cmd->args[0]) != 0)
			return (0);
		if (!change_pwd(env, "PWD="))
			return (0);
	}
	else
	{
		ft_putendl_fd("cd: no such a file or directory", 2);
		return (1);
	}
	return (1);
}

int	cd_oldpwd(t_cmd_array *cmd, t_env *env)
{
	t_env	*temp;
	char	*path;

	temp = search_key("OLDPWD=", env);
	if (temp)
	{
		env = env->first;
		path = temp->value;
		ft_putendl_fd(path, 2);
		if (access(path, F_OK) == 0)
		{
			if (!change_pwd(env, "OLDPWD="))
				return (0);
			if (chdir(path) != 0)
			{
				perror("chdir");
				return (0);
			}
			if (!change_pwd(env, "PWD="))
				return (0);
		}
	}
	else
		ft_putendl_fd("cd: no such a file or directory", 2);
	return (1);
}

int	change_pwd(t_env *env, char *pwd_oldpwd_flag)
{
	t_env	*temp;
	char	*pwd;

	temp = search_key(pwd_oldpwd_flag, env);
	if (temp)
	{
		env = temp;
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (0);
		replace_node(env, pwd);
		env = env->first;
	}
	return (1);
}
