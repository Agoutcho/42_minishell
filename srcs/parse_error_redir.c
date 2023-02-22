/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:26:16 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	find_the_redir(t_data *command, char *str, long i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		exit_error(str[i], str, command);
}

static int	is_redir_ok(char *str, long i, t_data *command)
{
	if (str[i] != '>' && str[i] != '<')
		return (1);
	if (str[i] == '>' && str[i + 1] != '>')
	{
		i++;
		find_the_redir(command, str, i);
	}
	else if (str[i] == '<' && str[i + 1] != '<')
	{
		i++;
		find_the_redir(command, str, i);
	}
	else
	{
		i += 2;
		find_the_redir(command, str, i);
	}
	return (1);
}

void	check_redir(t_data *command)
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
				&& !is_redir_ok(command->input, i, command))
			exit_error(command->input[i], command->input, command);
		i++;
	}
}
