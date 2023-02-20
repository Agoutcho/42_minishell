/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:28:07 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 18:30:33 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_pipe_ok(char *str, long i, t_command *command)
{
	if (str[i] == '|')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '|')
			exit_error(str[i], str, command);
	}
	return (1);
}

void	check_pipe(t_command *command)
{
	long	i;

	i = 0;
	command->quote = e_no_quote;
	while (command->input[i])
	{
		if (command->input[i] == '"' && command->quote == e_no_quote)
			command->quote = e_big_quote;
		else if (command->input[i] == '"' && command->quote == e_big_quote)
			command->quote = e_no_quote;
		if (command->input[i] == '\'' && command->quote == e_no_quote)
			command->quote = e_little_quote;
		else if (command->input[i] == '\'' && command->quote == e_little_quote)
			command->quote = e_no_quote;
		if (command->quote == e_no_quote \
				&& !is_pipe_ok(command->input, i, command))
			exit_error(command->input[i], command->input, command);
		i++;
	}
}
