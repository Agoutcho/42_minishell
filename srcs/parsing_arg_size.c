/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:57:23 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 21:38:52 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_lenght_in_env(t_command *command, char *str)
{
	t_env	*temp;

	temp = command->env->first;
	if (!*str)
		return (0);
	while (temp)
	{
		if (ft_strncmp(temp->key, str, ft_strlen(str) + 1) == 0)
			return (ft_strlen(temp->value));
		temp = temp->next;
	}
	return (0);
}

// check_special => '~' // TODO check ~/ ~+ ~-
// check $- $$ $?  $"" $
int	count_arg_size(t_command *c, char *str, long i)
{
	int	counter;

	counter = 0;
	if (c->quote != e_no_quote && str[i] == (char)c->quote)
		c->quote = e_no_quote;
	while (str[i] && !is_stop_char(c, str[i]))
	{
		set_quote(c, &i, 1);
		if (str[i] && str[i] == '$' && c->quote != e_little_quote)
			counter += count_dollar_size(c, str, &i, &counter);
		else if (str[i] && c->quote == e_no_quote && is_tilde_ok(str, i))
			counter += count_tilde_size(c, str, &i);
		else if (str[i] && c->quote != e_no_quote && str[i] != (char)c->quote)
		{
			i++;
			counter++;
		}
		else if (str[i] && c->quote == e_no_quote && !is_stop_char(c, str[i]) \
				&& str[i] != '\'' && str[i] != '"')
		{
			i++;
			counter++;
		}
	}
	return (counter);
}
