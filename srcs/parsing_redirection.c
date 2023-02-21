/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:45:25 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/21 01:34:05 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_type(t_command *command, long i_cmd, long *i, long *k)
{
	if (command->input[*i] == '>' && command->input[(*i) + 1] == '>')
		command->cmd_array[i_cmd].redir_array[*k].type = e_append;
	else if (command->input[*i] == '>' && command->input[(*i) + 1] != '>')
		command->cmd_array[i_cmd].redir_array[*k].type = e_out;
	else if (command->input[*i] == '<' && command->input[(*i) + 1] == '<')
		command->cmd_array[i_cmd].redir_array[*k].type = e_heredoc;
	else if (command->input[*i] == '<' && command->input[(*i) + 1] != '<')
		command->cmd_array[i_cmd].redir_array[*k].type = e_in;
	GREEN
	DEBUG("type : %d", command->cmd_array[i_cmd].redir_array[*k].type)
	RESET
	if (command->cmd_array[i_cmd].redir_array[*k].type == e_append \
			|| command->cmd_array[i_cmd].redir_array[*k].type == e_heredoc)
		(*i) = (*i) + 2;
	else
		(*i)++;
}

void	do_redirection(t_command *command, long ic, long *i, long *k)
{
	int	arg_size;

	add_type(command, ic, i, k);
	if (command->quote == e_no_quote)
		move_space(command->input, i);
	arg_size = count_arg_size(command, command->input, *i);
	command->cmd_array[ic].redir_array[*k].file_name = add_command(command, \
			command->input, i, arg_size);
	GREEN
	DEBUG("command->cmd_array[%ld].redir_array[%ld].file_name : %s", ic, *k, command->cmd_array[ic].redir_array[*k].file_name)
	RESET
	(*k)++;
}
