/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tilde_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:03:37 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:25:46 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_tilde_ok(char *str, long i)
{
	if (str[i] != '~')
		return (0);
	i++;
	if ((i == 1 || str[i - 2] == ' ') && (!str[i] || str[i] == ' ' \
		|| str[i] == '/' || str[i] == ':' || str[i] == '+' || str[i] == '-' \
		|| str[i] == '<' || str[i] == '>' || str[i] == '|'))
	{
		if ((str[i] == '+' || str[i] == '-') && (str[i + 1] \
			&& str[i + 1] != ' ' && str[i + 1] != '/' && str[i + 1] != ':' \
			&& str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != '|'))
			return (0);
		return (1);
	}
	return (0);
}

int	count_tilde_size(t_data *data, char *str, long *i)
{
	int	ret_value;
	int	temp_i;

	(*i)++;
	temp_i = *i;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	if (str[temp_i] == '+')
		ret_value = find_lenght_in_env(data, "PWD=");
	else if (str[temp_i] == '-')
		ret_value = find_lenght_in_env(data, "OLDPWD=");
	else
		ret_value = find_lenght_in_env(data, "HOME=");
	if (ret_value == 0 && (str[temp_i] == '-' || str[temp_i] == '+'))
		ret_value = 2;
	else if (ret_value == 0)
		ret_value = 1;
	return (ret_value);
}
