/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:31:00 by nradal            #+#    #+#             */
/*   Updated: 2023/03/05 17:52:01 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections_closer(t_cmd_array *cmd, t_fd_saver fd_saver)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (cmd->redir_size > i)
	{
		if (j == 0 && cmd->redir_array[i].type == e_heredoc)
		{
			unlink("/tmp/heredoc_file");
			if (cmd->redir_array[i].file_fd != -1 \
				&& close(cmd->redir_array[i].file_fd) == -1)
			{
				perror("close");
				return (0);
			}
			j++;
		}
		else if (cmd->redir_array[i].file_fd != -1 \
			&& close(cmd->redir_array[i].file_fd) == -1)
			return (0);
		// if (access(cmd->redir_array[i].file_name, W_OK) == 0)
		// {
			// if (close(cmd->redir_array[i].file_fd) == -1)
				// return (0);
		// }
		i++;
	}
	dup2(fd_saver.stdin, 0);
	dup2(fd_saver.stdout, 1);
	dup2(fd_saver.stderr, 2);
	return (1);
}

void heredoc_print(char *heredoc)
{
	ft_putstr_fd("-Rachele: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(heredoc, 2);
	ft_putstr_fd("')\n", 2);
}