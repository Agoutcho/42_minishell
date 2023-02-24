/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:38:58 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 04:53:25 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_cmd_array *cmd, t_env *env)
{
	if (!cmd->args || !cmd->args[0])
		return (cd_home(cmd, env));
	if (cmd->args[1])
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

int	cd_home(t_cmd_array *cmd, t_env *env)
{
	t_env	*temp;

	temp = search_key("HOME=", env);
	env = env->first;
	if (temp)
	{
		if (access(temp->value, F_OK) == 0)
		{
			if (!change_pwd(env, "OLDPWD="))
				return (0);
			if (chdir(temp->value) != 0)
			{
				perror("chdir");
				return (0);
			}
			if (!change_pwd(env, "PWD="))
				return (0);
		}
	}
	else
		ft_putendl_fd("cd : HOME not set", 2);
	return (1);
}

int	cd_oldpwd(t_cmd_array *cmd, t_env *env)
{
	t_env	*temp;
	char	*path;

	temp = search_key("OLDPWD=", env);
	env = env->first;
	if (temp)
	{
		path = ft_strdup(temp->value);
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
		free(path);
	}
	else
		ft_putendl_fd("cd : OLDPWD not set", 2);
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
	}
	env = env->first;
	return (1);
}
