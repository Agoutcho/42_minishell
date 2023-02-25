/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:06:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/25 01:18:22 by atchougo         ###   ########.fr       */
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

int	fill_heredoc(t_redirect *data, char *heredoc)
{
	data->heredoc = NULL;
	while (1)
	{
		data->hd_line = readline("> ");
		if (!data->hd_line)
		{
			ft_putstr_fd("-Rachele: warning: here-document delimited ", 1);
			ft_putstr_fd("by end-of-file (wanted `", 1);
			ft_putstr_fd(heredoc, 1);
			ft_putstr_fd("')\n", 1);
			secure_char_free(data->hd_line);
			return (0);
		}
		if (ft_strncmp(data->hd_line, heredoc, ft_strlen(heredoc) + 1) == 0)
			break ;
		add_heredoc(data);
		secure_char_free(data->hd_line);
	}
	secure_char_free(data->hd_line);
	return (1);
}
