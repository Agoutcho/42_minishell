/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:09:21 by nradal            #+#    #+#             */
/*   Updated: 2023/03/04 15:48:40 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_create_pipe(t_data *data, int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("Rachele: pipe");
		return (0);
	}
	//DEBUG("[%s] PIPES -> [in/%d][out/%d]", data->cmd[i].the_cmd, fd[0], fd[1]);
	if (data->cmd[i].fd_out == STDOUT_FILENO && i + 1 != data->size_cmd_array)
		data->cmd[i].fd_out = fd[1];
	else
		close(fd[1]);
	if (data->cmd[i + 1].fd_in == STDIN_FILENO)
		data->cmd[i + 1].fd_in = fd[0];
	else
		close(fd[0]);
	//DEBUG("[%s] PIPES -> [in/%d][out/%d]", data->cmd[i].the_cmd, data->cmd[i].fd_in, data->cmd[i].fd_out);
	return (1);
}

int	ft_connect_pipe(t_cmd_array *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)// && cmd->fd_in != -1)
	{
		//DEBUG("[%s] DUP2 [fd_in/%d] <-> [stdin/%d]",cmd->the_cmd, cmd->fd_in, STDIN_FILENO)
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("Rachele: dup2");
		if (close(cmd->fd_in) == -1)
			perror("Rachele: close");
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		//DEBUG("[%s] DUP2 [fd_out/%d] <-> [stdout/%d]",cmd->the_cmd, cmd->fd_out, STDOUT_FILENO)
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("Rachele: dup2");
		if (close(cmd->fd_out) == -1)
			perror("Rachele: close");
	}
	return (1);
}

int	ft_close_pipe(t_cmd_array *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
		close(cmd->fd_out);
	return (1);
}

void	ft_close_child_fd(t_data *data, int current)
{
	int	i;

	i = 0;
	while (i < data->size_cmd_array)
	{
		if (i != current)
		{
			ft_close_pipe(&data->cmd[i]);
		}
		i++;
	}
}