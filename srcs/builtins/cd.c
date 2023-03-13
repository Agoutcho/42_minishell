/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:38:58 by nradal            #+#    #+#             */
/*   Updated: 2023/03/13 16:57:25 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	cd_move(t_cmd_array *cmd, t_env *env);

int	ft_cd(t_cmd_array *cmd, t_env *env)
{
	if (!cmd->args || !cmd->args[0])
		return (cd_home(env));
	if (cmd->args[1])
	{
		ft_putendl_fd("Rachele: cd: too many arguments", 2);
		return (set_g_exit_code(1, 1));
	}
	else if (cmd->args[0][0] == '-' && cmd->args[0][1] == '\0')
		return (cd_oldpwd(env));
	else if (is_directory(cmd->args[0]))
	{
		if (!cd_move(cmd, env))
			return (0);
	}
	return (1);
}

int	cd_move(t_cmd_array *cmd, t_env *env)
{
	if (!change_pwd(env, "OLDPWD="))
		return (0);
	if (chdir(cmd->args[0]) != 0)
	{
		ft_putstr_fd("Rachele: cd: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (set_g_exit_code(1, 0));
	}
	if (!change_pwd(env, "PWD="))
		return (0);
	return (set_g_exit_code(0, 1));
}

// int	cd_move(t_cmd_array *cmd, t_env *env)
// {
// 	char	**split_path;
// 	int		i;

// 	i = 0;
	// split_path = ft_split(cmd->args[0], '/');
// 	if (!split_path)
// 		return (0);
// 	if (!change_pwd(env, "OLDPWD="))
// 		return (free_strs(split_path), 0);
// 	while (split_path[i])
// 	{
// 		if (access(split_path[i], F_OK) != 0)
// 			break ;
// 		if (chdir(split_path[i]) != 0)
// 			return (free_strs(split_path), 0);
// 		i++;
// 	}
// 	free_strs(split_path);
// 	if (!change_pwd(env, "PWD="))
// 		return (0);
// 	return (1);
// }

int	cd_home(t_env *env)
{
	t_env	*temp;

	temp = search_key("HOME=", env);
	env = env->first;
	if (temp)
	{
		if (!is_directory(temp->value))
			return (1);
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
	else
	{
		ft_putendl_fd("Rachele: cd: HOME not set", 2);
		return (set_g_exit_code(1, 1));
	}
	return (set_g_exit_code(0, 1));
}

int	cd_oldpwd(t_env *env)
{
	t_env	*temp;
	char	*path;

	temp = search_key("OLDPWD=", env);
	env = env->first;
	if (temp)
	{
		path = ft_strdup(temp->value);
		if (is_directory(path))
		{
			if (!change_pwd(env, "OLDPWD="))
				return (0);
			if (chdir(path) != 0)
				return (perror("chdir"), 0);
			if (!change_pwd(env, "PWD="))
				return (0);
		}
		ft_pwd(env);
		free(path);
	}
	else
	{
		ft_putendl_fd("Rachele: cd: OLDPWD not set", 2);
		return (set_g_exit_code(1, 1));
	}
	return (set_g_exit_code(0, 1));
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
			return (1);
		replace_node(env, pwd);
		free(pwd);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		create_node(env, pwd_oldpwd_flag, pwd);
		free(pwd);
	}
	env = env->first;
	return (1);
}

int	is_directory(char *path)
{
	DIR	*dir;

	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("Rachele: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such a file or directory", 2);
		return (set_g_exit_code(1, 0));
	}
	dir = opendir(path);
	if (dir != NULL)
		return (closedir(dir), 1);
	else
	{
		ft_putstr_fd("Rachele: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
		return (set_g_exit_code(1, 0));
	}
}
