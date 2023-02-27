/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 06:01:14 by atchougo         ###   ########.fr       */
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

int	exit_error(char c, char *input, t_data *data)
{
	int	fd;

	fd = STDERR_FILENO;
	(void)input;
	ft_putstr_fd("Rachele: syntax error near unexpected token `", fd);
	ft_putchar_fd(c, fd);
	ft_putstr_fd("'\n", fd);
	free_cmd(data);
	return (set_g_exit_code(2, 0));
}

int	check_parse_error(t_data *data)
{
	long	i;
	int		fd;

	fd = STDERR_FILENO;
	i = 0;
	data->quote = e_no_quote;
	if (!check_redir(data) && !check_pipe(data) && !check_quotes(data))
		return (set_g_exit_code(2, 0));
	if (move_space(data->input, &i) == -1)
		return (1);
	if (data->input[i] == '|')
	{
		ft_putstr_fd("Rachele: syntax error near unexpected token `|'\n", fd);
		free_cmd(data);
		return (set_g_exit_code(2, 0));
	}
	return (1);
}
