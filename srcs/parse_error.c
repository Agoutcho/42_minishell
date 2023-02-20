/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 04:17:17 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_last_value_ok(char *str, int i)
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

void	print_quote_error(t_command *command, char *str)
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

long	move_space(char *str, long *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
		return (-1);
	return (*i);
}

void	exit_error(char c, char *input, t_command *command)
{
	int	fd;

	fd = STDERR_FILENO;
	free(input);
	ft_putstr_fd("Rachele: syntax error near unexpected token `", fd);
	ft_putchar_fd(c, fd);
	ft_putstr_fd("'\n", fd);
	big_free(command);
	exit(2);
}

void	find_the_redir(t_command *command, char *str, long i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		exit_error(str[i], str, command);
}

int	is_redir_ok(char *str, long i, t_command *command)
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

void	check_redir(t_command *command)
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

int	is_pipe_ok(char *str, long i, t_command *command)
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

void	check_parse_error(t_command *command)
{
	long	i;
	int	fd;

	fd = STDERR_FILENO;
	i = 0;
	command->quote = e_no_quote;
	check_redir(command);
	check_pipe(command);
	check_quotes(command);
	if (move_space(command->input, &i) == -1)
		return ;
	if (command->input[i] == '|')
	{
		free(command->input);
		ft_putstr_fd("Rachele: syntax error near unexpected token `|'\n", fd);
		big_free(command);
		exit(2);
	}
}
