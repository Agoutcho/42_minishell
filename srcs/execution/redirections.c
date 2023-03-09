/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:12:09 by nradal            #+#    #+#             */
/*   Updated: 2023/03/09 10:51:55 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections_handler(t_cmd_array *cmd)
{
	int			i;
	t_redirect	*redir;

	i = 0;
	while (cmd->redir_size > i)
	{
		redir = &cmd->redir_array[i];
		if (redir->type == e_out && !e_out_handler(redir, cmd))
			return (0);
		else if (redir->type == e_append && !e_append_handler(redir, cmd))
			return (0);
		else if (redir->type == e_in && !e_in_handler(redir, cmd))
			return (0);
		i++;
	}
	if (is_hd(cmd))
	{
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
			close(cmd->fd_in);
		cmd->fd_in = cmd->heredoc_fd;
	}
	return (1);
}

int	is_hd(t_cmd_array *cmd)
{
	int	i;
	int	n_in;
	int	n_hd;

	i = 0;
	n_in = 0;
	n_hd = 0;
	while (cmd->redir_size > i)
	{
		if (cmd->redir_array[i].type == e_heredoc)
			n_hd = i;
		else if (cmd->redir_array[i].type == e_in)
			n_in = i;
		i++;
	}
	if (n_hd > n_in)
		return (1);
	else
		return (0);
}

int	e_out_handler(t_redirect *redir, t_cmd_array *cmd)
{
	redir->file_fd = open(redir->file_name,
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(redir->file_name, W_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (set_g_exit_code(1, 0));
	}
	if (redir->file_fd == -1)
	{
		perror("Rachele: open");
		return (set_g_exit_code(1, 0));
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (close(cmd->fd_out) == -1)
		{
			perror("Rachele: close");
			return (set_g_exit_code(1, 0));
		}
	}
	cmd->fd_out = redir->file_fd;
	return (1);
}

int	e_append_handler(t_redirect *redir, t_cmd_array *cmd)
{
	redir->file_fd = open(redir->file_name,
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(redir->file_name, W_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (set_g_exit_code(1, 0));
	}
	if (redir->file_fd == -1)
	{
		perror("Rachele: open");
		return (set_g_exit_code(1, 0));
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (close(cmd->fd_out) == -1)
		{
			perror("Rachele: close");
			return (set_g_exit_code(1, 0));
		}
	}
	cmd->fd_out = redir->file_fd;
	return (1);
}

int	e_in_handler(t_redirect *redir, t_cmd_array *cmd)
{
	redir->file_fd = open(redir->file_name, O_RDONLY);
	if (access(redir->file_name, F_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (set_g_exit_code(1, 0));
	}
	if (access(redir->file_name, R_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (set_g_exit_code(1, 0));
	}
	if (redir->file_fd == -1)
		return (perror("Rachele: open"), set_g_exit_code(1, 0));
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (close(cmd->fd_in) == -1)
			return (perror("Rachele: close"), set_g_exit_code(1, 0));
	}
	cmd->fd_in = redir->file_fd;
	return (1);
}
