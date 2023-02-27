/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:28:47 by nradal            #+#    #+#             */
/*   Updated: 2023/02/27 02:13:21 by atchougo         ###   ########.fr       */
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
		if (ptr->affiche_env == 1)
		{
			if (!ptr->key || !ptr->value)
				return (set_g_exit_code(1, 0));
			ft_putstr_fd(ptr->key, 1);
			ft_putendl_fd(ptr->value, 1);
		}
		ptr = ptr->next;
	}
	return (set_g_exit_code(0, 1));
}
