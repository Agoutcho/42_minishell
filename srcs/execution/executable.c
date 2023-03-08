/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:21:16 by nradal            #+#    #+#             */
/*   Updated: 2023/03/08 10:05:07 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_executable(t_data *data, int i)
{
	DIR *dir;
	if (access(data->cmd[i].the_cmd, F_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(data->cmd[i].the_cmd, 2);
		ft_putendl_fd(": No such a file or directory", 2);
		free_exit (data, 127);
	}
	if (access(data->cmd[i].the_cmd, X_OK))
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(data->cmd[i].the_cmd, 2);
		ft_putendl_fd(": permission denied", 2);
		free_exit (data, 126);
	}
	dir = opendir(data->cmd[i].the_cmd);
    if (dir != NULL)
	{
        closedir(dir);
        ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(data->cmd[i].the_cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_exit (data, 126);
    }
	return (1);
}

int	is_executable(t_data *data, int i)
{
	if (!data->cmd[i].the_cmd)
		return (-1);
	if  (ft_strncmp(data->cmd[i].the_cmd, "./", 2) == 0)
	{
		if (is_valid_executable(data, i) == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	executable_handler(t_data *data, int i)
{
	char	*cmd;
	char	**args;
	char	**env_array;

	args = NULL;
	cmd = ft_strdup(data->cmd[i].the_cmd);
	if (!cmd)
		free_exit(data, EXIT_FAILURE);
	env_array = env_to_array(data->env);
	if (!env_array)
		free_exit(data, EXIT_FAILURE);
	big_free(data);
	execve(cmd, args, env_array);
	if (data->cmd[i].fd_in != STDIN_FILENO)
		close(data->cmd[i].fd_in);
	if (data->cmd[i].fd_in != STDOUT_FILENO)
		close(data->cmd[i].fd_out);
	secure_char_free(&cmd);
	free_strs(env_array);
	exit (256);
}
