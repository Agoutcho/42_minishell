/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:29:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 18:30:43 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	print_quote_error(t_command *command, char *str)
{
	int	fd;

	fd = STDERR_FILENO;
	free(command->input);
	ft_putstr_fd("Rachele: unexpected EOF while looking for matching `", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("'\nRachele: syntax error: unexpected end of file\n", fd);
	big_free(command);
	exit(2);
}

void	check_quotes(t_command *command)
{
	long	i;

	i = 0;
	command->quote = e_no_quote;
	while (command->input[i])
	{
		set_quote(command, &i, 0);
		i++;
	}
	if (command->quote == e_big_quote)
		print_quote_error(command, "\"");
	if (command->quote == e_little_quote)
		print_quote_error(command, "'");
	if (!is_last_value_ok(command->input, i))
	{
		free(command->input);
		big_free(command);
		exit(2);
	}
}
