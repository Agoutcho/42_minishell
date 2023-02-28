/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:06:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/28 03:58:04 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_heredoc(t_redirect *data)
{
	t_heredoc	*new;

	new = (t_heredoc *)malloc(sizeof(t_heredoc));
	new->line = ft_strdup(data->hd_line);
	new->next = NULL;
	if (data->heredoc)
	{
		new->first = data->heredoc->first;
		while (data->heredoc->next)
			data->heredoc = data->heredoc->next;
		data->heredoc->next = new;
	}
	else
	{
		data->heredoc = new;
		data->heredoc->first = new;
	}
}

static int forked_heredoc(t_redirect *data, char *heredoc)
{
	int save_in;

	save_in = dup(STDIN_FILENO);
	int	temp;
	// signal(SIGINT, sig_handler_heredoc);
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, SIG_DFL);

	// sig_action();
	temp = 0;
	g_exit_code = open("/tmp/heredoc_file", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (g_exit_code == -1)
		exit (1);
	DEBUG()
	while (1)
	{
		DEBUG()
		data->hd_line = readline("> ");
		if (!data->hd_line && g_exit_code != -1)
		{
			ft_putstr_fd("-Rachele: warning: here-document delimited ", 1);
			ft_putstr_fd("by end-of-file (wanted `", 1);
			ft_putstr_fd(heredoc, 1);
			ft_putstr_fd("')\n", 1);
			secure_char_free(data->hd_line);
			exit (0);
		}
		if (ft_strncmp(data->hd_line, heredoc, ft_strlen(heredoc) + 1) == 0 \
		|| ft_strncmp(data->hd_line, heredoc, ft_strlen(heredoc) + 1) == -1)
			break ;
		// add_heredoc(data);
		ft_putendl_fd(data->hd_line, g_exit_code);
		secure_char_free(data->hd_line);
	}
	DEBUG()
	if (g_exit_code == -1)
	{
		dup2(save_in, STDIN_FILENO);
		g_exit_code = open("/tmp/heredoc_file", O_RDWR | O_TRUNC | O_CREAT, 0600);
		perror(strerror(errno));
		DEBUG("g_exit_code : %d", g_exit_code);
		temp = 130;
	}
	if (close(g_exit_code))
		exit (1);
	secure_char_free(data->hd_line);
	// big_free(data);
	exit (temp);
}

int	fill_heredoc(t_redirect *data, char *heredoc)
{
	pid_t	pid;
	int		status;

	status = 0;
	data->heredoc = NULL;
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		forked_heredoc(data, heredoc);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (set_g_exit_code(status, 0));
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	DEBUG("status : %d", status)
	if (status != 0)
		return (set_g_exit_code(status, 0));
	return (1);
}
