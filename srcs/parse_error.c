/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	move_space(char *str, long *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
		return (-1);
	return (*i);
}

void	exit_error(char c, char *input, t_data *command)
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

void	check_parse_error(t_data *command)
{
	long	i;
	int		fd;

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
