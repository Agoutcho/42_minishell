/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:07:26 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 21:12:21 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_dol_env(t_command *command, long *i, char *parsed, long *index)
{
	int		size_dollar;
	int		temp_i;
	char	*temp_key;
	char	*str;

	str = command->input;
	temp_i = *i;
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
	temp_key = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp_key)
		big_free(command);
	temp_key[size_dollar] = 0;
	temp_key[--size_dollar] = '=';
	while (size_dollar-- > 0)
		temp_key[size_dollar] = str[(*i) + size_dollar];
	find_val_in_env(command, temp_key, parsed, index);
	(*i) += temp_i - *i;
	free(temp_key);
}

void	adding_qmark(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;

	i_val = 0;
	temp = ft_itoa(g_exit_code);
	if (!temp)
		big_free(command);
	while (temp[i_val])
	{
		parsed[*index] = temp[i_val];
		(*index)++;
		i_val++;
	}
	(*i)++;
	free(temp);
}

void	adding_hyphen(t_command *command, long *i, char *parsed, long *index)
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
			break ;
		}
		tenv = tenv->next;
	}
	(*i)++;
	free(temp);
}

// check $- $$ $?  $"" $
// TODO peut etre ajouter '$_' => la derniere variable connue  https://abs.traduc.org/abs-5.3-fr/ch09.html
void	add_dollar(t_command *command, long *i, char *temp, long *index)
{
	char	*str;

	str = command->input;
	if (command->quote == e_no_quote \
			&& (str[(*i) + 1] == '\'' || str[(*i) + 1] == '"'))
	{
		(*i)++;
		return ;
	}
	else if (!is_dollar_ok(str, i, 0))
	{
		temp[*index] = str[*i];
		(*index)++;
		(*i)++;
		return ;
	}
	(*i)++;
	if (str[*i] == '-')
		adding_hyphen(command, i, temp, index);
	else if (str[*i] == '?')
		adding_qmark(command, i, temp, index);
	else
		add_dol_env(command, i, temp, index);
}
