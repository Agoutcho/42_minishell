/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:29:00 by nradal            #+#    #+#             */
/*   Updated: 2023/02/20 04:06:13 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_shlvl(char *env_value)
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

int	copy_env(t_command *command, char **env)
{
	int		j;
	t_env	*first;

	first = (t_env *)malloc(sizeof(t_env));
	if (!first)
		return (0);
	command->env = first;
	command->env->first = first;
	command->env->next = NULL;
	if (!lst_add_env_value(env[0], command->env))
		return (0);
	j = 1;
	while (env[j])
	{
		if (!lst_add_back_env(command, env, j))
			return (0);
		j++;
	}
	return (1);
}

static int	free_create_env(char *pwd, char *join, char *temp, int v)
{
	tout_free(pwd);
	tout_free(join);
	tout_free(temp);
	return (v);
}

int create_env(t_command *command)
{
    t_env	*first;
	char	*temp;
	char	*pwd;
	char	*join;

    first = (t_env *)malloc(sizeof(t_env));
	if (!first)
		return (0);
	command->env = first;
	command->env->first = first;
	command->env->next = NULL;
	if (!lst_add_env_value("SHLVL=0", command->env))
		return (0);
	if (!add_to_env(command, "OLDPWD"))
		return (0);
	pwd = ft_strdup("PWD=");
	temp = getcwd(NULL, 0);
	join = ft_strjoin(pwd, temp);
	if (!add_to_env(command, join))
		return (free_create_env(pwd, join, temp, 0));
	return (free_create_env(pwd, join, temp, 1));
}

int	init_env(t_command *command, char **env)
{
	if (env[0] != NULL && !copy_env(command, env))
		return (0);
	else if (env[0] == NULL && !create_env(command))
	    return (0);
	return (1);
}
