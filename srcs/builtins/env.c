/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:28:47 by nradal            #+#    #+#             */
/*   Updated: 2023/03/13 14:39:43 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*ptr;

	if (!env)
		return (set_g_exit_code(1, 0));
	ptr = env->first;
	while (ptr != NULL)
	{
		if (ptr->display_env == 1)
		{
			if (!ptr->key || !ptr->value)
				return (set_g_exit_code(1, 0));
			ft_putstr_fd(ptr->key, STDOUT_FILENO);
			ft_putendl_fd(ptr->value, STDOUT_FILENO);
		}
		ptr = ptr->next;
	}
	return (set_g_exit_code(0, 1));
}
