/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:25:46 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	move_space(char *str, long *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		return (-1);
	return (*i);
}

void	exit_error(char c, char *input, t_data *data)
{
	int	fd;

	fd = STDERR_FILENO;
	free(input);
	ft_putstr_fd("Rachele: syntax error near unexpected token `", fd);
	ft_putchar_fd(c, fd);
	ft_putstr_fd("'\n", fd);
	big_free(data);
	exit(2);
}

void	check_parse_error(t_data *data)
{
	long	i;
	int		fd;

	fd = STDERR_FILENO;
	i = 0;
	data->quote = e_no_quote;
	check_redir(data);
	check_pipe(data);
	check_quotes(data);
	if (move_space(data->input, &i) == -1)
		return ;
	if (data->input[i] == '|')
	{
		free(data->input);
		ft_putstr_fd("Rachele: syntax error near unexpected token `|'\n", fd);
		big_free(data);
		exit(2);
	}
}
