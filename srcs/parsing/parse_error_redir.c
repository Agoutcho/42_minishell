/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:26:16 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 05:33:05 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_the_redir(t_data *data, char *str, long i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (exit_error(str[i], str, data));
}

static int	is_redir_ok(char *str, long i, t_data *data)
{
	int	res;

	res = 1;
	if (str[i] != '>' && str[i] != '<')
		return (1);
	if (str[i] == '>' && str[i + 1] != '>')
	{
		i++;
		res = find_the_redir(data, str, i);
	}
	else if (str[i] == '<' && str[i + 1] != '<')
	{
		i++;
		res = find_the_redir(data, str, i);
	}
	else
	{
		i += 2;
		res = find_the_redir(data, str, i);
	}
	return (res);
}

int	check_redir(t_data *data)
{
	long	i;

	i = 0;
	data->quote = e_no_quote;
	while (data->input[i])
	{
		if (data->input[i] == '"' && data->quote == e_no_quote)
			data->quote = e_big_quote;
		else if (data->input[i] == '"' && data->quote == e_big_quote)
			data->quote = e_no_quote;
		if (data->input[i] == '\'' && data->quote == e_no_quote)
			data->quote = e_little_quote;
		else if (data->input[i] == '\'' && data->quote == e_little_quote)
			data->quote = e_no_quote;
		if (data->quote == e_no_quote \
				&& !is_redir_ok(data->input, i, data))
			return (0);
		i++;
	}
	return (1);
}
