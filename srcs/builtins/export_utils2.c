/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:42:17 by nradal            #+#    #+#             */
/*   Updated: 2023/03/13 14:37:18 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_e_print(char *str)
{
	ft_putstr_fd("Rachele: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

int	export_search_and_update_key(char *key, char *value, t_env **env)
{
	t_env	*temp;

	temp = search_key(key, *env);
	if (temp)
	{
		if (ft_strcmp(key, temp->key) == 61)
		{
			free(temp->key);
			temp->key = ft_strdup(key);
		}
		*env = temp;
		if (value)
		{
			if (!replace_node(*env, value))
				return (0);
		}
	}
	else
	{
		if (*env)
			*env = (*env)->first;
		return (0);
	}
	return (1);
}

int	export_create_node(char *key, char *value, t_env **env)
{
	if (*env)
		*env = (*env)->first;
	if (!create_node(*env, key, value))
		return (0);
	return (1);
}
