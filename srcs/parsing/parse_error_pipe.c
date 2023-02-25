/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:28:07 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:25:46 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_pipe_ok(char *str, long i, t_data *data)
{
	if (str[i] == '|')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '|')
			exit_error(str[i], str, data);
	}
	return (1);
}

void	check_pipe(t_data *data)
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
				&& !is_pipe_ok(data->input, i, data))
			exit_error(data->input[i], data->input, data);
		i++;
	}
}
