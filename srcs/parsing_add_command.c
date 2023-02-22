/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:41:37 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*sec_malloc(t_data *command, char *str, long *i, int size)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
	{
		big_free(command);
		exit(2);
	}
	if (command->quote != e_no_quote && str[*i] == (char)command->quote)
		command->quote = e_no_quote;
	return (temp);
}

static int	is_dollar_quoted(t_quote quote, char c)
{
	if (quote == e_big_quote && c == '$')
		return (0);
	return (1);
}

static void	add_qtd_value(t_data *command, char *temp, long *i, long *index)
{
	char	*str;

	str = command->input;
	while (str[*i] != (char)command->quote \
			&& is_dollar_quoted(command->quote, str[*i]))
	{
		temp[*index] = str[*i];
		(*index)++;
		(*i)++;
	}
}

char	*add_command(t_data *c, char *str, long *i, int size)
{
	char	*temp;
	long	index;

	index = 0;
	temp = sec_malloc(c, str, i, size);
	while (str[*i] && !is_stop_char(c, str[*i]))
	{
		set_quote(c, i, 1);
		if (str[*i] && str[*i] == '$' && c->quote != e_little_quote)
			add_dollar(c, i, temp, &index);
		else if (str[*i] && c->quote == e_no_quote && is_tilde_ok(str, *i))
			add_tilde(c, i, temp, &index);
		else if (str[*i] && c->quote != e_no_quote && str[*i] != (char)c->quote)
			add_qtd_value(c, temp, i, &index);
		else if (str[*i] && c->quote == e_no_quote && !is_stop_char(c, str[*i]) \
				&& str[*i] != '\'' && str[*i] != '"')
		{
			temp[index] = str[*i];
			index++;
			(*i)++;
		}
	}
	temp[index] = 0;
	return (temp);
}
