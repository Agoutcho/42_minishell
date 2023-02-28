/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:31:00 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 10:27:33 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections_closer(t_cmd_array *cmd, t_fd_saver fd_saver)
{
	int	i;

	i = 0;
	while (cmd->redir_size > i)
	{
		if (cmd->redir_array[i].type == e_heredoc)
		{
			unlink("/tmp/heredoc_file");
		}
		// if (access(cmd->redir_array[i].file_name, W_OK) == 0)
		// {
			if (close(cmd->redir_array[i].file_fd) == -1)
			{
				perror("close");
				return (0);
			}
		// }
		i++;
	}
	dup2(fd_saver.stdin, 0);
	dup2(fd_saver.stdout, 1);
	dup2(fd_saver.stderr, 2);
	return (1);
}
