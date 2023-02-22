/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:35 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 19:55:43 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static void	init_to_zero(long *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static int	malloc_r_array(t_command *command, int j, int *counter_redir)
{
	int i;

	i = 0;
	command->cmd_array[j].redir_size = *counter_redir;
	command->cmd_array[j].redir_array = \
		(t_redirect *)malloc(sizeof(t_redirect) * (*counter_redir));
	if (!command->cmd_array[j].redir_array)
	{
		big_free(command);
		exit(2);
	}
	while (i < *counter_redir)
	{
		command->cmd_array[j].redir_array[i].file_name = NULL;
		command->cmd_array[j].redir_array[i].heredoc = NULL;
		command->cmd_array[j].redir_array[i].file_fd = 0;
		command->cmd_array[j].redir_array[i].type = 0;
		i++;
	}
	*counter_redir = 0;
	return (1);
}

static int	is_no_quote(t_command *command, long i)
{
	if (command->input[i] && command->quote == e_no_quote)
		return (1);
	return (0);
}

void	init_redir(t_command *command)
{
	long	i;
	int		j;
	int		counter_redir;

	init_to_zero(&i, &j, &counter_redir);
	command->cmd_array[j].redir_size = 0;
	command->quote = e_no_quote;
	while (command->input[i])
	{
		set_quote(command, &i, 1);
		if (is_no_quote(command, i) && is_redir(command->input[i]))
			counter_redir++;
		if (is_no_quote(command, i) && command->input[i] == '|')
			j += malloc_r_array(command, j, &counter_redir);
		if ((command->input[i] == '<' || command->input[i] == '>') \
			&& (command->input[i + 1] == '<' || command->input[i + 1] == '>'))
			i++;
		if (command->input[i])
			i++;
	}
	malloc_r_array(command, j, &counter_redir);
}
