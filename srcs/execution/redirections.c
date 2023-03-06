/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:12:09 by nradal            #+#    #+#             */
/*   Updated: 2023/03/05 17:39:31 by nradal           ###   ########.fr       */
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
		else if (redir->type == e_heredoc && !e_heredoc_handler(redir, cmd))
			return (0);
		i++;
	}
	return (1);
}

// int e_heredoc_handler(t_redirect *redir, t_cmd_array *cmd)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;
// 	char	*heredoc_line;

// 	redir->file_fd = -1;
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Rachele: pipe");
// 		return (0);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Rachele: pid");
// 		return (0);
// 	}
// 	else if (pid == 0)
// 	{
// 		signal(SIGINT, sig_int_child_handler);
// 		signal(SIGQUIT, SIG_DFL);

// 		if (close(pipe_fd[0]) == -1)
// 		{
// 			perror("Rachele: close");
// 			exit (EXIT_FAILURE);
// 		}
// 		while (1)
// 		{
// 			heredoc_line = readline("> ");
// 			if (!heredoc_line && g_exit_code != -1)
// 			{
// 				ft_putstr_fd("-Rachele: warning: here-document delimited ", 2);
// 				ft_putstr_fd("by end-of-file (wanted `", 2);
// 				ft_putstr_fd("EOF", 2);
// 				ft_putstr_fd("')\n", 2);
// 				free(heredoc_line);
// 				exit (EXIT_FAILURE);
// 			}
// 			if (ft_strncmp(heredoc_line, "EOF", 3 + 1) == 0 || ft_strncmp(heredoc_line, "EOF", 3 + 1) == -1)
// 			{
// 				free(heredoc_line);
// 				break ;
// 			}
// 			ft_putendl_fd(heredoc_line, pipe_fd[1]);
// 			free(heredoc_line);
// 		}
// 		if (close(pipe_fd[1]) == -1)
// 		{
// 			perror("Rachele: close");
// 			exit (EXIT_FAILURE);
// 		}
// 		exit (EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		if (close(pipe_fd[1]) == -1)
// 		{
// 			perror("Rachele: close");
// 			exit (EXIT_FAILURE);
// 		}
// 		if (waitpid(pid, &status, 0) == -1)
// 		{
// 			perror("Rachele: waitpid");
// 			return (0);
// 		}
// 		if (status == 1)
// 		{
// 			if (close(pipe_fd[0]) == -1)
// 			{
// 				perror("Rachele: close");
// 				exit (EXIT_FAILURE);
// 			}
// 			return (1);
// 		}
// 		if (cmd->fd_in != STDIN_FILENO)
// 		{
// 			if (close(cmd->fd_in) == -1)
// 			{
// 				perror("Rachele: close");
// 				return (set_g_exit_code(1, 0));
// 			}
// 		}
// 		cmd->fd_in = pipe_fd[0];
// 	}
// 	return (1);
// }

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
	if (access(redir->file_name, R_OK) != 0)
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
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (close(cmd->fd_in) == -1)
		{
			perror("Rachele: close");
			return (set_g_exit_code(1, 0));
		}
	}
	cmd->fd_in = redir->file_fd;
	return (1);
}
