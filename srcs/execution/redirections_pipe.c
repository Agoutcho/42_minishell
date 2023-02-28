/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:41:35 by nradal            #+#    #+#             */
/*   Updated: 2023/02/28 19:33:18 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_create_pipe(t_command *cmd)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERROR)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->fd->out == STDOUT_FILENO)
		cmd->fd->out = fd[1];
	else
		close(fd[1]);
	if (cmd->next->fd->in == STDIN_FILENO)
		cmd->next->fd->in = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	ft_connect_pipe(t_command *cmd)
{
	if (cmd->fd->in != STDIN_FILENO && cmd->fd->in != RETURN_ERROR)
	{
		dup2(cmd->fd->in, STDIN_FILENO);
		close(cmd->fd->in);
	}
	if (cmd->fd->out != STDOUT_FILENO)
	{
		dup2(cmd->fd->out, STDOUT_FILENO);
		close(cmd->fd->out);
	}
	return (0);
}

int	ft_close_pipe(t_command *cmd)
{
	if (cmd->fd->in != STDIN_FILENO && cmd->fd->in != RETURN_ERROR)
		close(cmd->fd->in);
	if (cmd->fd->out != STDOUT_FILENO)
		close(cmd->fd->out);
	return (0);
}