/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:09:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 13:59:14 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_env *env)
{
	t_env	*temp;

	if (env)
	{
		temp = env->first;
		while (temp->next != env)
			temp = temp->next;
		temp->next = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}

t_env	*search_key(char *key, t_env *env)
{
	int	i;

	i = ft_strlen(key);
	if (key[i - 1] != '=')
	{
		key = ft_strjoin(key, "=");
		if (!key)
		{
			ft_putendl_fd("unset, export: something went wrong", 2);
			return (NULL);
		}
	}
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	replace_node(t_env *env, char *value)
{
	if (env->value)
		free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
		return (0);
	return (1);
}

int	env_ll_len(t_env *env_list)
{
	int		ll_len;
	t_env	*ptr;

	ll_len = 0;
	ptr = env_list;
	while (ptr != NULL)
	{
		ll_len++;
		ptr = ptr->next;
	}
	return (ll_len);
}

char	**env_to_array(t_env *env_list)
{
	int		i;
	int		ll_len;
	char	**env_array;
	t_env	*ptr;

	ll_len = env_ll_len(env_list);
	env_array = malloc((ll_len + 1) * (sizeof(char *)));
	if (!env_array)
		return (NULL);
	ptr = env_list;
	i = 0;
	while (ptr)
	{
		env_array[i] = ft_strjoin(ptr->key, ptr->value);
		if (!env_array[i])
		{
			free_strs(env_array);
			return (NULL);
		}
		i++;
		ptr = ptr->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
