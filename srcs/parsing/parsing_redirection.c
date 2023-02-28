/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:45:25 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/28 17:56:46 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_type(t_data *data, long i_cmd, long *i, long *k)
{
	if (data->input[*i] == '>' && data->input[(*i) + 1] == '>')
		data->cmd[i_cmd].redir_array[*k].type = e_append;
	else if (data->input[*i] == '>' && data->input[(*i) + 1] != '>')
		data->cmd[i_cmd].redir_array[*k].type = e_out;
	else if (data->input[*i] == '<' && data->input[(*i) + 1] == '<')
		data->cmd[i_cmd].redir_array[*k].type = e_heredoc;
	else if (data->input[*i] == '<' && data->input[(*i) + 1] != '<')
		data->cmd[i_cmd].redir_array[*k].type = e_in;
	if (data->cmd[i_cmd].redir_array[*k].type == e_append \
			|| data->cmd[i_cmd].redir_array[*k].type == e_heredoc)
		(*i) = (*i) + 2;
	else
		(*i)++;
}

void	do_redirection(t_data *data, long i_cmd, long *i, long *k)
{
	int	arg_size;

	add_type(data, i_cmd, i, k);
	if (data->quote == e_no_quote)
		move_space(data->input, i);
	arg_size = count_arg_size(data, data->input, *i);
	data->cmd[i_cmd].redir_array[*k].file_name = add_command(data, \
			data->input, i, arg_size);
	data->cmd[i_cmd].redir_array[*k].file_fd = -1;
	(*k)++;
}
