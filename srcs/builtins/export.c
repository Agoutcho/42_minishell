/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:33:48 by nradal            #+#    #+#             */
/*   Updated: 2023/03/11 22:16:15 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmd_array *cmd, t_env *env)
{
	int	i;

	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		if (!ft_export_no_args(env))
			return (set_g_exit_code(1, 0));
	}
	else
	{
		i = 0;
		g_exit_code = 0;
		while (cmd->args[i])
		{
			if (is_valid_arg(cmd->args[i]))
			{
				if (!handle_export_arg(cmd->args[i], &env))
					return (set_g_exit_code(1, 0));
			}
			else
			{
				export_e_print(cmd->args[i]);
				g_exit_code = 1;
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
	int		result;

	if (!split_arg_on_equal_sign(arg, &key, &value))
		return (0);
	result = export_search_and_update_key(key, value, env);
	if (!result)
		result = export_create_node(key, value, env);
	free_key_value(key, value);
	return (result);
}

int	ft_is_portable_charset(char c)
{
	if (ft_isalnum(c) || c == '!' || c == '"' || c == '#' || c == '$'
		|| c == '%' || c == '&' || c == '\'' || c == '(' || c == ')'
		|| c == '*' || c == '+' || c == ',' || c == '-' || c == '.'
		|| c == '/' || c == ':' || c == ';' || c == '<' || c == '='
		|| c == '>' || c == '?' || c == '@' || c == '[' || c == '\\'
		|| c == ']' || c == '^' || c == '_' || c == '`' || c == '{'
		|| c == '|' || c == '}' || c == '~' || c == ' ')
		return (1);
	return (0);
}

int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i++]) == 0)
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 1 || arg[i] == '_')
			i++;
		else
			return (0);
	}
	while (arg[i])
	{
		if (ft_is_portable_charset(arg[i]))
			i++;
		else
			return (0);
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
