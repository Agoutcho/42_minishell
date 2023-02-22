/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:05:09 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 02:28:18 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	from_list_to_char(t_data *data, long j)
{
	t_args	*temp;
	int		args_counter;
	int		i;

	i = 0;
	args_counter = 0;
	temp = data->cmd[j].arg->first;
	while (temp)
	{
		args_counter++;
		temp = temp->next;
	}
	data->cmd[j].args = (char **)malloc(sizeof(char *) * (args_counter + 1));
	if (!data->cmd[j].args)
	{
		big_free(data);
		exit(1);
	}
	temp = data->cmd[j].arg->first;
	while (temp)
	{
		data->cmd[j].args[i] = ft_strdup(temp->arg);
		temp = temp->next;
        i++;
	}
    data->cmd[j].args[i] = NULL;
}

void	transform_args(t_data *data)
{
	long	j;

    j = 0;
    while (j < data->size_cmd_array)
    {
        if (data->cmd[j].arg)
            from_list_to_char(data, j);
        j++;
    }
}