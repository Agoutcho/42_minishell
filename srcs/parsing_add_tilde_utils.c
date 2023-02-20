/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_tilde_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:22:23 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 23:17:17 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_til_in_env(t_command *command, char *t_key, char *parsed, long *idex)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = command->env->first;
	while (temp)
	{
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
			while (temp->value[i])
			{
				parsed[*idex] = temp->value[i];
				(*idex)++;
				i++;
			}
			parsed[*idex] = 0;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int	ret_val(long *i, char *temp, int i_val, int value)
{
	(*i) = (*i) + value;
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (i_val);
}

int	add_tilde_home(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first;
	temp = ft_strdup("HOME=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	return (ret_val(i, temp, i_val, 1));
}

int	add_tilde_plus(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first;
	temp = ft_strdup("PWD=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	return (ret_val(i, temp, i_val, 2));
}

int	add_tilde_hyphen(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first;
	temp = ft_strdup("OLDPWD=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	return (ret_val(i, temp, i_val, 2));
}
