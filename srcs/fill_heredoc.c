/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:06:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/16 23:32:56 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_heredoc(t_command *command)
{
    t_heredoc *new;

    new = (t_heredoc *)malloc(sizeof(t_heredoc));
    new->line = ft_strdup(command->hd_line);
    new->next = NULL;
    if (command->heredoc)
    {
        new->first = command->heredoc->first;
        while (command->heredoc->next)
            command->heredoc = command->heredoc->next;
        command->heredoc->next = new;
    }
    else
    {
        command->heredoc = new;
        command->heredoc->first = new;
    }
}

int	fill_heredoc(t_command *command, char *heredoc)
{
    command->heredoc = NULL;
    while (1)
    {
        command->hd_line = readline("> ");
        if (!command->hd_line)
        {
            ft_putstr_fd("-Rachele: warning: here-document delimited ", 1);
            ft_putstr_fd("by end-of-file (wanted `", 1);
            ft_putstr_fd(heredoc, 1);
            ft_putstr_fd("')\n", 1);
            tout_free(command->hd_line);
            return (0);
        }
        DEBUG("%s", command->hd_line);
        if (ft_strncmp(command->hd_line, heredoc, ft_strlen(heredoc) + 1) == 0)
            break ;
        add_heredoc(command);
        tout_free(command->hd_line);
    }
	tout_free(command->hd_line);
	return (1);
}