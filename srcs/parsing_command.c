/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:52:34 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/24 05:21:24 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_args	*add_args(t_data *data, long *i, long i_cmd)
{
	t_args	*temp;
	int		arg_size;

	arg_size = count_arg_size(data, data->input, *i);
	temp = (t_args *)malloc(sizeof(t_args));
	if (!temp)
		big_free(data);
	temp->next = NULL;
	temp->arg = add_command(data, data->input, i, arg_size);
	if (data->cmd[i_cmd].arg)
	{
		temp->first = data->cmd[i_cmd].arg->first;
		data->cmd[i_cmd].arg->next = temp;
	}
	else
		temp->first = temp;
	return (temp);
}

void	do_command(t_data *data, long i_cmd, long *i)
{
	int	arg_size;

	arg_size = count_arg_size(data, data->input, *i);
	if (data->cmd[i_cmd].is_cmd_filled == 0)
	{
		data->cmd[i_cmd].is_cmd_filled = 1;
		data->cmd[i_cmd].the_cmd = add_command(data, \
				data->input, i, arg_size);
		// RED
		// DEBUG("data->cmd[%ld].the_cmd : %s", i_cmd, data->cmd[i_cmd].the_cmd)
		// RESET
	}
	else
	{
		data->cmd[i_cmd].arg = add_args(data, i, i_cmd);
		// YELLOW
		// DEBUG("data->cmd[%ld].arg : %s", i_cmd, data->cmd[i_cmd].arg->arg)
		// RESET
	}
}
