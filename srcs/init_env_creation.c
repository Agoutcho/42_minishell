/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:09:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 18:14:59 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*change_shlvl(char *env_value)
{
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(env_value) + 1);
	free(env_value);
	return (shlvl);
}

int	lst_add_env_value(char *envp, t_env *env)
{
	int	key_len;
	int	value_len;

	key_len = 0;
	value_len = 0;
	if (!envp)
		return (0);
	while (envp[key_len] != '=')
		key_len++;
	while (envp[value_len + key_len])
		value_len++;
	env->key = (char *)malloc(sizeof(char) * key_len + 1);
	if (!env->key)
		return (0);
	env->value = (char *)malloc(sizeof(char) * value_len + 1);
	if (!env->value)
		return (0);
	ft_strlcat(env->key, envp, key_len + 2);
	ft_strlcpy(env->value, envp + key_len + 1, value_len + 2);
	if (ft_strncmp(env->key, "SHLVL=", ft_strlen(env->key) + 1) == 0)
		env->value = change_shlvl(env->value);
	env->affiche_env = 1;
	return (1);
}

int	lst_add_back_env(t_command *command, char **env, int j)
{
	t_env	*new;
	t_env	*temp;

	temp = command->env;
	while (temp->next)
		temp = temp->next;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->first = temp->first;
	new->next = NULL;
	temp->next = new;
	if (!lst_add_env_value(env[j], new))
		return (0);
	return (1);
}
