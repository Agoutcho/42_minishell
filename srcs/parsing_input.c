/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_stop_char(t_data *command, char c)
{
	if (command->quote != e_no_quote)
		return (0);
	else if (command->quote == e_no_quote && !is_redir(c) && c != '|' \
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

void	parsing_input(t_data *command)
{
	long			i;
	long			j;
	long			k;

	i = 0;
	j = 0;
	k = 0;
	command->quote = e_no_quote;
	command->cmd_array[0].args = NULL;
	while (j < command->size_cmd_array && command->input[i])
	{
		if (command->quote == e_no_quote)
			move_space(command->input, &i);
		set_quote(command, &i, 0);
		if (command->quote == e_no_quote && command->input[i] == '|')
		{
			j++;
			i++;
			k = 0;
		}
		else if (command->quote == e_no_quote && is_redir(command->input[i]))
			do_redirection(command, j, &i, &k);
		else if (command->input[i])
			do_command(command, j, &i);
	}
}
