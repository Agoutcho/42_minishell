/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:12:09 by nradal            #+#    #+#             */
/*   Updated: 2023/03/01 03:13:16 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections_handler(t_cmd_array *cmd)
{
	int			i;
	t_redirect	*redir;
	size_t in[2];

	in[0] = 0;
	in[1] = 0;
	i = 0;
	while (cmd->redir_size > i)
	{
		redir = &cmd->redir_array[i];
		if (redir->type == e_in && !e_in_handler(redir, &in[0], i))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_out && !e_out_handler(redir))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_append && !e_append_handler(redir))
			return (cmd->redir_size = i, 0);
		else if (redir->type == e_heredoc && !e_hd_handler(redir, &in[1], i))
			return (cmd->redir_size = i, 0);
		i++;
	}
	if (i && (in[0] < in[1] || in[1] == 0))
	{
		redir = &cmd->redir_array[in[1]];
		return (e_in_handler(redir, &in[0], 0));
	}
	return (1);
}

int	e_hd_handler(t_redirect *redir, size_t *in_val, int i)
{
	int		test;

	(*in_val) = i;
	test = fill_heredoc(redir, redir->file_name);
	if (test == 0)
		return (0);
	redir->file_name = ft_strdup("/tmp/heredoc_file");
	return (1);
}

int	e_in_handler(t_redirect *redir, size_t *in_val, int i)
{
	(*in_val) = i;
	if (access(redir->file_name, R_OK) != 0)
	{
		ft_putstr_fd("Rachele: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (set_g_exit_code(1, 0));
	}
	redir->file_fd = open(redir->file_name, O_RDONLY);
	if (redir->file_fd == -1)
	{
		perror(redir->file_name);
		return (set_g_exit_code(1, 0));
	}
	if (dup2(redir->file_fd, 0) == -1)
	{
		perror("dup2");
		return (set_g_exit_code(1, 0));
	}
	return (1);
}

int	e_out_handler(t_redirect *redir)
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
		perror("open");
		return (set_g_exit_code(1, 0));
	}
	if (dup2(redir->file_fd, 1) == -1)
	{
		perror("dup2");
		return (set_g_exit_code(1, 0));
	}
	return (1);
}

int	e_append_handler(t_redirect *redir)
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
		perror("open");
		return (set_g_exit_code(1, 0));
	}
	if (dup2(redir->file_fd, 1) == -1)
	{
		perror("dup2");
		return (set_g_exit_code(1, 0));
	}
	return (1);
}
