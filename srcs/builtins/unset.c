/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:06:32 by nradal            #+#    #+#             */
/*   Updated: 2023/03/13 00:23:10 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void afficheee(t_env *env)
{
	t_env *temp;

	temp = env->first;
	while (temp)
	{
		DEBUG("temp key : %s temp : %p temp->next : %p", temp->key, temp, temp->next);
		temp = temp->next;
		usleep(100000);
	}
}

int	unset_keys(t_cmd_array *cmd, t_env **env)
{
	char	*key;
	t_env	*temp;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if ((!get_unset_key(cmd->args[i], &key))
			|| (ft_strlen(cmd->args[i]) == 0))
		{
			return (set_g_exit_code(0, 1));
		}
		else
		{
			temp = search_key(key, *env);
			if (temp)
			{
				*env = temp;
				afficheee(*env);
				DEBUG("REMOVE NODE *env : %p", *env)
				remove_node(env);
				DEBUG("NODE REMOVED *env : %p", *env)
				afficheee(*env);
			}
			*env = (*env)->first;
		}
		i++;
	}
	return (set_g_exit_code(0, 1));
}

int	ft_unset(t_cmd_array *cmd, t_env **env)
{
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (set_g_exit_code(0, 1));
	else
	{
		return (unset_keys(cmd, env));
	}
}

int	get_unset_key(char *arg, char **key)
{
	if (!ft_strchr(arg, '='))
	{
		*key = ft_strdup(arg);
		if (!(*key))
			return (0);
		return (1);
	}
	else
		return (0);
}
