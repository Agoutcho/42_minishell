/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:31:00 by nradal            #+#    #+#             */
/*   Updated: 2023/02/28 19:05:08 by atchougo         ###   ########.fr       */
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
