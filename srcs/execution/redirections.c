/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:12:09 by nradal            #+#    #+#             */
/*   Updated: 2023/02/25 03:40:35 by atchougo         ###   ########.fr       */
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
		if (redir->type == e_in && !e_in_handler(redir))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_out && !e_out_handler(redir))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_append && !e_append_handler(redir))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_heredoc && !e_heredoc_handler(redir))
			return (cmd->redir_size = i, 0);
		i++;
	}
	return (1);
}

int	e_heredoc_handler(t_redirect *redir)
{
	t_heredoc	*temp;
	int			test;

	test = fill_heredoc(redir, redir->file_name);
	if (test == 0)
		return (0);
	redir->file_fd = open("/tmp/heredoc_file", O_RDWR | O_CREAT, 0600);
	if (redir->file_fd == -1)
	{
		perror("open");
		return (0);
	}
	temp = redir->heredoc->first;
	while (temp)
	{
		ft_putendl_fd(temp->line, redir->file_fd);
		temp = temp->next;
	}
	if (close(redir->file_fd))
	{
		perror("close");
		return (0);
	}
	redir->file_name = ft_strdup("/tmp/heredoc_file");
	return (e_in_handler(redir));
}

int	e_in_handler(t_redirect *redir)
{
	redir->file_fd = open(redir->file_name, O_RDONLY);
	if (redir->file_fd == -1)
	{
		perror(redir->file_name);
		return (0);
	}
	if (dup2(redir->file_fd, 0) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}

int	e_out_handler(t_redirect *redir)
{
	redir->file_fd = open(redir->file_name,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (redir->file_fd == -1)
	{
		perror("open");
		return (0);
	}
	if (dup2(redir->file_fd, 1) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}

int	e_append_handler(t_redirect *redir)
{
	redir->file_fd = open(redir->file_name,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (redir->file_fd == -1)
	{
		perror("open");
		return (0);
	}
	if (dup2(redir->file_fd, 1) == -1)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}
