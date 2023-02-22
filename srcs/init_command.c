/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:15:24 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:25:46 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_cmd_filled(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->size_cmd_array)
	{
		data->cmd_array[i].the_cmd = NULL;
		data->cmd_array[i].args = NULL;
		data->cmd_array[i].is_cmd_filled = 0;
		data->cmd_array[i].redir_size = 0;
		data->cmd_array[i].redir_array = NULL;
		i++;
	}
}

void	set_quote(t_data *data, long *i, int change_i)
{
	int	previous_quote;

	previous_quote = data->quote;
	if (data->input[*i] == '"' && data->quote == e_no_quote)
		data->quote = e_big_quote;
	else if (data->input[*i] == '"' && data->quote == e_big_quote)
		data->quote = e_no_quote;
	if (data->input[*i] == '\'' && data->quote == e_no_quote)
		data->quote = e_little_quote;
	else if (data->input[*i] == '\'' && data->quote == e_little_quote)
		data->quote = e_no_quote;
	if (change_i && previous_quote != (int)data->quote)
		(*i)++;
}

void	init_command(t_data *data)
{
	long		i;
	int			counter_command;
	t_cmd_array	*temp;

	i = 0;
	counter_command = 1;
	data->quote = e_no_quote;
	while (data->input[i])
	{
		set_quote(data, &i, 0);
		if (data->quote == e_no_quote && data->input[i] == '|')
			counter_command++;
		i++;
	}
	data->size_cmd_array = counter_command;
	temp = (t_cmd_array *)malloc(sizeof(t_cmd_array) * counter_command);
	data->cmd_array = temp;
	init_cmd_filled(data);
}
