/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:03:47 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 15:50:18 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_key_length(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (++i);
		i++;
	}
	return (i);
}

char	*get_key(char *arg)
{
	char	*key;
	int		i;
	int		len;

	i = 0;
	len = get_key_length(arg);
	key = malloc((len + 1) * sizeof(char));
	if (!key)
		return (NULL);
	while (i < len)
	{
		key[i] = arg[i];
		i++;
	}
	key[len] = '\0';
	return (key);
}

char	*get_value(char *arg)
{
	char	*value;
	size_t	i;
	int		j;

	i = get_key_length(arg);
	j = 0;
	if (i == ft_strlen(arg))
		return (ft_strdup("''"));
	value = malloc((ft_strlen(arg) - i + 1) * sizeof(char));
	if (!value)
		return (NULL);
	while (arg[i])
	{
		value[j] = arg[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int	ft_export_no_args(t_env *env)
{
	char	**env_array;
	char	**env_array_not_sorted;
	int		i;

	if (env)
	{
		env_array_not_sorted = env_to_array(env);
		if (!env_array_not_sorted)
			return (0);
		env_array = sort_strs(env_array_not_sorted);
		if (!env_array)
			return (0);
		else
		{
			i = 0;
			while (env_array[i])
			{
				ft_putendl_fd(env_array[i], 1);
				i++;
			}
		}
		free_strs(env_array_not_sorted);
	}
	return (1);
}

char	**sort_strs(char **strs)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	i = 0;
	size = 0;
	while (strs[size])
		size++;
	while (i < size - 1)
	{
		j = i;
		while (j < size)
		{
			if (ft_strcmp(strs[j], strs[i]) < 0)
			{
				temp = strs[i];
				strs[i] = strs[j];
				strs[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (strs);
}
