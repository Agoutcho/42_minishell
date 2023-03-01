/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/03/01 02:52:39 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stop_char(t_data *data, char c)
{
	if (data->quote != e_no_quote)
		return (0);
	else if (data->quote == e_no_quote && !is_redir(c) && c != '|' \
			&& c != ' ' && c != '\t' && c != '\n' && c != '\r' && c)
		return (0);
	return (1);
}

void	find_val_in_env(t_data *com, char *t_key, char *parsed, long *idex)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = com->env->first;
	while (temp)
	{
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
			while (temp->value[i])
			{
				parsed[*idex] = temp->value[i];
				(*idex)++;
				i++;
			}
			return ;
		}
		temp = temp->next;
	}
}

void	parsing_input(t_data *data)
{
	long			input;
	long			j_cmd;
	long			k_redir;

	input = 0;
	j_cmd = 0;
	k_redir = 0;
	data->quote = e_no_quote;
	data->cmd[0].arg = NULL;
	while (j_cmd < data->size_cmd_array && data->input[input])
	{
		if (data->quote == e_no_quote)
			move_space(data->input, &input);
		set_quote(data, &input, 0);
		if (data->quote == e_no_quote && data->input[input] == '|')
		{
			j_cmd++;
			input++;
			k_redir = 0;
		}
		else if (data->quote == e_no_quote && is_redir(data->input[input]))
			do_redirection(data, j_cmd, &input, &k_redir);
		else if (data->input[input])
			do_command(data, j_cmd, &input);
	}
}
