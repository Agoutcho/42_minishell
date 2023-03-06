/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:07:46 by nradal            #+#    #+#             */
/*   Updated: 2023/03/06 14:06:00 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_exit(t_data *data, int exit_value)
{
	big_free(data);
	exit(exit_value);
}