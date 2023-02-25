/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:07:46 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 05:18:55 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	if (data)
	{
		//free_cmd_array(data->cmd);
		//free_env(data->env);
	}
}

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		if (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
		}
		i++;
	}
	free(strs);
	strs = NULL;
}
