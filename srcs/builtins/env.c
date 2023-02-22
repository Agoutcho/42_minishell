/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:28:47 by nradal            #+#    #+#             */
/*   Updated: 2023/02/09 17:41:48 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*ptr;

	if (!env)
		return (0);
	ptr = env->first;
	while (ptr != NULL)
	{
		if (ptr->affiche_env == 1)
		{
			if (!ptr->key || !ptr->value)
				return (0);
			ft_putstr_fd(ptr->key, 1);
			ft_putendl_fd(ptr->value, 1);
		}
		ptr = ptr->next;
	}
	return (1);
}
