/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_closer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:01:36 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 10:06:09 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_closer(t_data *data, int i)
{
	if (data->size_cmd_array <= 1)
		return (1);
	else if (i == 0)
		return (close_first_pipe(data, i));
	else if (i + 1 == data->size_cmd_array)
		return (close_last_pipe(data, i));
	else
		return (close_middle_pipe(data, i));
}

int	close_first_pipe(t_data *data, int i)
{
	ft_memcpy(data->cmd[i + 1].pipe_fd, data->cmd[i].pipe_fd,
		sizeof(data->cmd[i].pipe_fd));
	if (close(data->cmd[i].pipe_fd[1]))
	{
		perror("close");
		return (0);
	}
	return (1);
}

int	close_last_pipe(t_data *data, int i)
{
	if (close(data->cmd[i].pipe_fd[0]))
	{
		perror("close");
		return (0);
	}
	return (1);
}

int	close_middle_pipe(t_data *data, int i)
{
	ft_memcpy(data->cmd[i + 1].pipe_fd, data->cmd[i].pipe_fd,
		sizeof(data->cmd[i].pipe_fd));
	if (close(data->cmd[i].pipe_fd[1]))
	{
		perror("close");
		return (0);
	}
	if (close(data->cmd[i].multiple_pipe))
	{
		perror("close");
		return (0);
	}
	return (1);
}
