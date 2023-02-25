/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:29:00 by nradal            #+#    #+#             */
/*   Updated: 2023/02/22 18:44:38 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	copy_env(t_data *data, char **env)
{
	int		j;
	t_env	*first;

	first = (t_env *)malloc(sizeof(t_env));
	if (!first)
		return (0);
	data->env = first;
	data->env->first = first;
	data->env->next = NULL;
	data->env->key = NULL;
	data->env->value = NULL;
	data->env->affiche_env = 0;
	if (!lst_add_env_value(env[0], data->env))
		return (0);
	j = 1;
	while (env[j])
	{
		if (!lst_add_back_env(data, env, j))
			return (0);
		j++;
	}
	return (1);
}

static int	free_create_env(char *pwd, char *join, char *temp, int v)
{
	secure_char_free(pwd);
	secure_char_free(join);
	secure_char_free(temp);
	return (v);
}

static int	create_env(t_data *data)
{
	t_env	*first;
	char	*temp;
	char	*pwd;
	char	*join;

	first = (t_env *)malloc(sizeof(t_env));
	if (!first)
		return (0);
	data->env = first;
	data->env->first = first;
	data->env->next = NULL;
	data->env->key = NULL;
	data->env->value = NULL;
	data->env->affiche_env = 0;
	if (!lst_add_env_value("SHLVL=0", data->env))
		return (0);
	if (!add_to_env(data, "OLDPWD"))
		return (0);
	pwd = ft_strdup("PWD=");
	temp = getcwd(NULL, 0);
	join = ft_strjoin(pwd, temp);
	if (!add_to_env(data, join))
		return (free_create_env(pwd, join, temp, 0));
	return (free_create_env(pwd, join, temp, 1));
}

int	init_env(t_data *data, char **env)
{
	if (env[0] != NULL && !copy_env(data, env))
		return (0);
	else if (env[0] == NULL && !create_env(data))
		return (0);
	return (1);
}
