/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:56:13 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/23 00:57:18 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arg_lst(t_data *data, long i)
{
	t_args	*targs;

	targs = data->cmd[i].arg;
	secure_char_free(targs->arg);
	data->cmd[i].arg = data->cmd[i].arg->next;
	free(targs);
	targs = NULL;
}

void	free_args_char(t_data *data, long i)
{
	long	j;

	j = 0;
	while (data->cmd[i].args[j])
	{
		secure_char_free(data->cmd[i].args[j]);
		j++;
	}
	if (data->cmd[i].args)
		free(data->cmd[i].args);
	data->cmd[i].args = NULL;
}
