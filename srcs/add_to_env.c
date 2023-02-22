/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:53:37 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	add_printable(char *str, t_env *env)
{
	int		key_len;
	int		value_len;

	key_len = 0;
	value_len = 0;
	while (str[key_len] != '=')
		key_len++;
	while (str[value_len + key_len])
		value_len++;
	env->key = (char *)malloc(sizeof(char) * key_len + 1);
	if (!env->key)
		return (0);
	env->value = (char *)malloc(sizeof(char) * value_len + 1);
	if (!env->value)
		return (0);
	ft_strlcat(env->key, str, key_len + 2);
	ft_strlcpy(env->value, str + key_len + 1, value_len + 2);
	env->affiche_env = check_printable(str);
	return (1);
}

static int	add_not_printable(char *str, t_env *env)
{
	int		key_len;

	key_len = 0;
	while (str[key_len])
		key_len++;
	env->key = (char *)malloc(sizeof(char) * key_len + 1);
	if (!env->key)
		return (0);
	ft_strlcat(env->key, str, key_len + 2);
	env->affiche_env = check_printable(str);
	return (1);
}

/**
 * @brief Add a new element in env list at the end 
 * 
 * @param command 
 * @param str The string to add like "var=lol"
 * @return int 
 */
int	add_to_env(t_data *command, char *str)
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
	if (check_printable(str))
		return (add_printable(str, new));
	else
		return (add_not_printable(str, new));
}

t_env	*find_env_value(t_data *command, char *key)
{
	char	*temp_key;
	t_env	*temp;

	temp = command->env->first;
	while (temp->next)
	{
		temp_key = temp->key;
		if (ft_strncmp(temp_key, key, ft_strlen(temp_key) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	temp_key = temp->key;
	if (ft_strncmp(temp_key, key, ft_strlen(temp_key) + 1) == 0)
		return (temp);
	return (NULL);
}
