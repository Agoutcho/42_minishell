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

void	error_executable_handler(char *path, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Rachele: no such a file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
	else if (error == 2)
	{
		ft_putstr_fd("Rachele: permission denied: ", 2);
		ft_putendl_fd(path, 2);
	}
}

bool	is_executable(char *path)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	i = len - 1;
	while (i >= 2 && path[i] != '/')
		i--;
	i -= 1;
	if (ft_strncmp(path + i, "./", 2) == 0)
	{
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (true);
			else
				error_executable_handler(path, 2);
		}
		else
			error_executable_handler(path, 1);
	}
	return (false);
}

int	executable_handler(t_cmd_array *cmd, t_env *env)
{
	pid_t	pid;
	char	**env_array;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		env_array = env_to_array(env);
		if (!env_array)
			return (0);
		execve(cmd->the_cmd, cmd->args, env_array);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("fork");
		return (0);
	}
	return (1);
}
