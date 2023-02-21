/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:52:34 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/21 01:34:01 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_args	*add_args(t_command *command, long *i, long i_cmd)
{
	t_args	*temp;
	int		arg_size;

	arg_size = count_arg_size(command, command->input, *i);
	temp = (t_args *)malloc(sizeof(t_args));
	if (!temp)
		big_free(command);
	temp->next = NULL;
	temp->arg = add_command(command, command->input, i, arg_size);
	if (command->cmd_array[i_cmd].args)
	{
		temp->first = command->cmd_array[i_cmd].args->first;
		command->cmd_array[i_cmd].args->next = temp;
	}
	else
		temp->first = temp;
	return (temp);
}

void	do_command(t_command *command, long i_cmd, long *i)
{
	int	arg_size;

	arg_size = count_arg_size(command, command->input, *i);
	if (command->cmd_array[i_cmd].is_cmd_filled == 0)
	{
		command->cmd_array[i_cmd].is_cmd_filled = 1;
		command->cmd_array[i_cmd].the_cmd = add_command(command, \
				command->input, i, arg_size);
		RED
		DEBUG("command->cmd_array[%ld].the_cmd : %s", i_cmd, command->cmd_array[i_cmd].the_cmd)
		RESET
	}
	else
	{
		command->cmd_array[i_cmd].args = add_args(command, i, i_cmd);
		YELLOW
		DEBUG("command->cmd_array[%ld].args : %s", i_cmd, command->cmd_array[i_cmd].args->arg)
		RESET
	}
}
