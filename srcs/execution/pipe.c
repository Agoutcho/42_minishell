/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:11:16 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 10:01:44 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_handler(t_data *data, int i)
{
	if (data->size_cmd_array <= 1)
		return (1);
	else if (i == 0)
		return (first_pipe_handler(data, i));
	else if (i + 1 == data->size_cmd_array)
		return (last_pipe_handler(data, i));
	else
		return (middle_pipe_handler(data, i));
}

int	first_pipe_handler(t_data *data, int i)
{
	if (pipe(data->cmd[i].pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}

int	last_pipe_handler(t_data *data, int i)
{
	if (dup2(data->cmd[i].pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}

int	middle_pipe_handler(t_data *data, int i)
{
	if (dup2(data->cmd[i].pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	data->cmd[i].multiple_pipe = data->cmd[i].pipe_fd[0];
	if (pipe(data->cmd[i].pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}
