/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:21:16 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 11:00:55 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_executable(char *path)
{
	DIR *dir;
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such a file or directory", 2);
		exit (127);
	}
	if (access(path, X_OK))
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": permission denied", 2);
		exit (126);
	}
	dir = opendir(path);
    if (dir != NULL)
	{
        closedir(dir);
        ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
        exit (126);
    }
	return (1);
}

int	is_executable(char *path)
{
	if (!path)
		return (-1);
	if  (ft_strncmp(path, "./", 2) == 0)
	{
		if (is_valid_executable(path) == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	executable_handler(t_cmd_array *cmd, t_env *env)
{
	char	**env_array;

	env_array = env_to_array(env);
	if (!env_array)
		return (0);
	execve(cmd->the_cmd, cmd->args, env_array);
	DEBUG("Execve failed executable")

	free_strs(env_array);
	return (0);
}
