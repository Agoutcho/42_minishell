/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:33:48 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 05:37:12 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmd_array *cmd, t_env *env)
{
	int	i;

	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		if (!ft_export_no_args(env))
			return (0);
	}
	else
	{
		i = 0;
		while (cmd->args[i])
		{
			if (is_valid_arg(cmd->args[i]))
			{
				if (!handle_export_arg(cmd->args[i], &env))
					return (0);
			}
			else
			{
				ft_putstr_fd("Rachele: export: `", 2);
				ft_putstr_fd(cmd->args[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
			}
			i++;
		}
	}
	return (1);
}

int	handle_export_arg(char *arg, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*temp;

	if (!split_arg_on_equal_sign(arg, &key, &value))
		return (0);
	temp = search_key(key, *env);
	DEBUG("%s", key)
	if (temp)
	{
		*env = temp;
		if (value)
			if (!replace_node(*env, value))
				return (0);
	}
	else
	{
		*env = (*env)->first;
		if (!create_node(*env, key, value))
			return (0);
	}
	if (key)
		free(key);
	if (value)
		free(value);
	return (1);
}

int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (!arg[i + 1])
				return (1);
			i++;
		}
		if (ft_isalnum(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	split_arg_on_equal_sign(char *arg, char **key, char **value)
{
	if (ft_strchr(arg, '='))
	{
		*key = get_key(arg);
		if (!(*key))
			return (0);
		*value = get_value(arg);
		if (!(*value))
		{
			free(*key);
			return (0);
		}
		return (1);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!(*key))
			return (0);
		*value = NULL;
		return (1);
	}
}
