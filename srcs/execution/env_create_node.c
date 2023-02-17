/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:24:22 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 13:28:21 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_node(t_env *env, char *key, char *value)
{
	if (!env || !key)
		return (0);
	while (env->next)
		env = env->next;
	env->next = init_new_node();
	if (!env->next)
		return (0);
	if (!set_key(env->next, key))
		return (0);
	if (!set_value(env->next, value))
		return (0);
	env->next->next = NULL;
	env->next->first = env->first;
	return (1);
}

t_env	*init_new_node(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->affiche_env = 0;
	return (node);
}

int	set_key(t_env *node, char *key)
{
	if (key[ft_strlen(key) - 1] != '=')
		node->key = ft_strjoin(key, "=");
	else
		node->key = ft_strdup(key);
	return (node->key != NULL);
}

int	set_value(t_env *node, char *value)
{
	if (value)
	{
		node->value = ft_strdup(value);
		node->affiche_env = 1;
	}
	else
	{
		node->value = ft_strdup("''");
		node->affiche_env = 0;
	}
	return (node->value != NULL);
}
