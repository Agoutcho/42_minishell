/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:35 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 06:09:24 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static void	init_to_zero(long *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static int	malloc_r_array(t_data *data, int j, int *counter_redir)
{
	int	i;

	i = 0;
	data->cmd[j].redir_size = *counter_redir;
	data->cmd[j].redir_array = \
		(t_redirect *)malloc(sizeof(t_redirect) * (*counter_redir));
	if (!data->cmd[j].redir_array)
	{
		big_free(data);
		exit(1);
	}
	while (i < *counter_redir)
	{
		data->cmd[j].redir_array[i].file_name = NULL;
		data->cmd[j].redir_array[i].heredoc = NULL;
		data->cmd[j].redir_array[i].file_fd = 0;
		data->cmd[j].redir_array[i].type = 0;
		i++;
	}
	*counter_redir = 0;
	return (1);
}

static int	is_no_quote(t_data *data, long i)
{
	if (data->input[i] && data->quote == e_no_quote)
		return (1);
	return (0);
}

void	init_redir(t_data *data)
{
	long	i;
	int		j;
	int		counter_redir;

	init_to_zero(&i, &j, &counter_redir);
	data->cmd[j].redir_size = 0;
	data->quote = e_no_quote;
	while (data->input[i])
	{
		set_quote(data, &i, 1);
		if (is_no_quote(data, i) && is_redir(data->input[i]))
			counter_redir++;
		if (is_no_quote(data, i) && data->input[i] == '|')
			j += malloc_r_array(data, j, &counter_redir);
		if ((data->input[i] == '<' || data->input[i] == '>') \
			&& (data->input[i + 1] == '<' || data->input[i + 1] == '>'))
			i++;
		if (data->input[i])
			i++;
	}
	malloc_r_array(data, j, &counter_redir);
}
