/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:28:47 by nradal            #+#    #+#             */
/*   Updated: 2023/03/04 15:44:10 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env, t_cmd_array *cmd)
{
	t_env	*ptr;

	if (!env)
		return (set_g_exit_code(1, 0));
	ptr = env->first;
	while (ptr != NULL)
	{
		if (ptr->affiche_env == 1)
		{
			if (!ptr->key || !ptr->value)
				return (set_g_exit_code(1, 0));
			ft_putstr_fd(ptr->key, cmd->fd_out);
			ft_putendl_fd(ptr->value, cmd->fd_out);
		}
		ptr = ptr->next;
	}
	return (set_g_exit_code(0, 1));
}
