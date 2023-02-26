/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:09:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/25 04:43:09 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_env *env)
{
	//danger leaks
	t_env	*temp;

	if (env)
	{
		temp = env->first;
		while (temp->next != env)
			temp = temp->next;
		temp->next = env->next;
		if (env->key)
		{
			free(env->key);
			env->key = NULL;
		}
		if (env->value)
		{
			free(env->value);
			env->value = NULL;	
		}
		free(env);
		env = NULL;
	}
}

t_env	*search_key(char *key, t_env *env)
{
	int		i;
	char	*temp_key;
	char	*temp_env_key;

	i = ft_strlen(key);
	if (key[i - 1] == '=')
	{
		temp_key = ft_substr(key, 0, i - 1);
		if (!temp_key)
		{
			return (NULL);
		}
	}
	else
		temp_key = ft_strdup(key);
	while (env)
	{
		i = ft_strlen(env->key);
		if (env->key[i - 1] == '=')
		{
			temp_env_key = ft_substr(env->key, 0, i - 1);
			if (!temp_env_key)
			{
				free(temp_key);
				return (NULL);
			}
		}
		else
			temp_env_key = ft_strdup(env->key);
		if (ft_strcmp(temp_key, temp_env_key) == 0)
		{
			free(temp_key);
			free(temp_env_key);
			return (env);
		}
		env = env->next;
		free(temp_env_key);
	}
	free(temp_key);
	return (NULL);
}

int	replace_node(t_env *env, char *value)
{
	if (env->value)
	{
		free(env->value);
		env->value = NULL;
	}
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

char	**env_to_array_plus_quotes(t_env *env_list)
{
	int		i;
	int		ll_len;
	char	**env_array;
	t_env	*ptr;
	char *quoted_value;

	ll_len = env_ll_len(env_list);
	env_array = malloc((ll_len + 1) * (sizeof(char *)));
	if (!env_array)
		return (NULL);
	ptr = env_list;
	i = 0;
	while (ptr)
	{
		quoted_value = ft_strjoin("\"", ptr->value);
		if (!quoted_value)
		{
			free_strs(env_array);
			return (NULL);
		}
		env_array[i] = ft_strjoin(ptr->key, quoted_value);
		free(quoted_value);
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
