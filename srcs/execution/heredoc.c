/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:37:54 by nradal            #+#    #+#             */
/*   Updated: 2023/03/06 21:29:49 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Rachele: pipe");
		return (0);
	}
	return (1);
}

int	close_pipe(int pipe_fd[2], int fd_index)
{
	if (close(pipe_fd[fd_index]) == -1)
	{
		perror("Rachele: close");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	child_process(int pipe_fd[2], char *heredoc)
{
	char	*heredoc_line;

	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, SIG_DFL);
	if (!close_pipe(pipe_fd, 0))
		exit(EXIT_FAILURE);
	while (1)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line && g_exit_code != -1)
		{
			heredoc_print("EOF");
			free(heredoc_line);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(heredoc_line, heredoc, ft_strlen(heredoc) + 1) == 0
			|| ft_strncmp(heredoc_line, heredoc, ft_strlen(heredoc) + 1) == -1)
			break ;
		ft_putendl_fd(heredoc_line, pipe_fd[1]);
		free(heredoc_line);
	}
	free(heredoc_line);
	if (!close_pipe(pipe_fd, 1))
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	parent_process(int pipe_fd[2], int *status, t_cmd_array *cmd, int pid)
{
	if (!close_pipe(pipe_fd, 1))
		return (0);
	if (waitpid(pid, status, 0) == -1)
		return (perror("Rachele: waitpid"), 0);
	if (*status == 1)
	{
		if (!close_pipe(pipe_fd, 0))
			exit(EXIT_FAILURE);
		return (1);
	}
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (close(cmd->fd_in) == -1)
		{
			perror("Rachele: close");
			return (set_g_exit_code(1, 0));
		}
	}
	cmd->fd_in = pipe_fd[0];
	return (1);
}

int	e_heredoc_handler(t_redirect *redir, t_cmd_array *cmd)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	redir->file_fd = -1;
	if (!create_pipe(pipe_fd))
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror("Rachele: pid");
		return (0);
	}
	else if (pid == 0)
		child_process(pipe_fd, redir->file_name);
	else
		return (parent_process(pipe_fd, &status, cmd, pid));
	return (1);
}
