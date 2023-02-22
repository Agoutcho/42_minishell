/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:00:31 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar_ok(char *str, long *i, int change_i)
{
	if ((str[*i] == '$' && str[(*i) + 1] != '-' && str[(*i) + 1] != '?' \
		&& !ft_isalnum(str[(*i) + 1])) || !str[(*i) + 1] \
		|| str[(*i) + 1] == ' ')
	{
		if (change_i)
			(*i)++;
		return (0);
	}
	return (1);
}

static int	count_dollar_special(t_data *command, char *str, long *i)
{
	char	*temp;
	int		result;

	if (str[*i] == '?')
	{
		(*i)++;
		temp = ft_itoa(g_exit_code);
		result = (int)ft_strlen(temp);
	}
	else
	{
		temp = ft_strdup("OLDPWD=");
		result = find_lenght_in_env(command, temp);
	}
	free(temp);
	return (result);
}

int	count_dollar_size(t_data *command, char *str, long *i, int *counter)
{
	int		size_dollar;
	int		temp_i;
	char	*temp;

	if (!is_dollar_ok(str, i, 1))
		return (1);
	(*i)++;
	temp_i = *i;
	if (str[*i] == '-' || str[*i] == '?')
		return (count_dollar_special(command, str, i));
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
	temp = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp)
		big_free(command);
	temp[size_dollar] = 0;
	temp[--size_dollar] = '=';
	while (size_dollar-- > 0)
		temp[size_dollar] = str[(*i) + size_dollar];
	*counter = (*counter) + find_lenght_in_env(command, temp);
	(*i) += temp_i - *i;
	free(temp);
	return (0);
}
