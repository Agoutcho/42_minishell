/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:29:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 05:55:53 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_last_value_ok(char *str, int i)
{
	int	f;

	f = STDERR_FILENO;
	while (i-- > 0 && str[i])
	{
		if (str[i] == '|')
		{
			ft_putstr_fd("Rachele: syntax error: unexpected end of file\n", f);
			return (0);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			ft_putstr_fd("Rachele: syntax error near ", f);
			ft_putstr_fd("unexpected token `newline'\n", f);
			return (0);
		}
		else if (str[i] != ' ')
			return (1);
	}
	return (1);
}

static int	print_quote_error(t_data *data, char *str)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("Rachele: unexpected EOF while looking for matching `", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("'\nRachele: syntax error: unexpected end of file\n", fd);
	free_cmd(data);
	return (set_g_exit_code(2, 0));
}

int	check_quotes(t_data *data)
{
	long	i;

	i = 0;
	data->quote = e_no_quote;
	while (data->input[i])
	{
		set_quote(data, &i, 0);
		i++;
	}
	if (data->quote == e_big_quote)
		return (print_quote_error(data, "\""));
	if (data->quote == e_little_quote)
		print_quote_error(data, "'");
	if (!is_last_value_ok(data->input, i))
	{
		free_cmd(data);
		return (set_g_exit_code(2, 0));
	}
	return (1);
}
