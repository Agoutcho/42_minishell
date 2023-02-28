/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:12:09 by nradal            #+#    #+#             */
/*   Updated: 2023/02/28 04:11:56 by atchougo         ###   ########.fr       */
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
	 	redir->save_std_in = dup(STDIN_FILENO);
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
	int		test;
	t_redirect *temp;

	temp = redir - 1;
	dup2(temp->save_std_in, STDIN_FILENO);
	DEBUG("redir->file_name %s", redir->file_name)
	test = fill_heredoc(redir, redir->file_name);
	if (test == 0)
		return (0);
	redir->file_name = ft_strdup("/tmp/heredoc_file");
	return (e_in_handler(redir));
}

int	e_in_handler(t_redirect *redir)
{
	if (access(redir->file_name, R_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (0);
	}
	redir->file_fd = open(redir->file_name, O_RDONLY);
	DEBUG("redir->file_fd : %d", redir->file_fd)
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
	if (access(redir->file_name, W_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (0);
	}
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
	if (access(redir->file_name, W_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (0);
	}
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
