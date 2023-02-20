/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_tilde.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:35:21 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/20 21:33:51 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	change_val_two(int temp_i, char *temp, long *i_temp, char *str)
{
	temp[*i_temp] = str[temp_i - 2];
	(*i_temp)++;
	temp[*i_temp] = str[temp_i - 1];
	(*i_temp)++;
	return (2);
}

static int	change_val_one(int temp_i, char *temp, long *i_temp, char *str)
{
	temp[*i_temp] = str[temp_i - 1];
	(*i_temp)++;
	return (1);
}

void	add_tilde(t_command *command, long *i, char *temp, long *i_temp)
{
	int		ret_value;
	int		temp_i;
	char	*str;

	str = command->input;
	temp_i = *i;
	temp_i++;
	if (str[temp_i] == '-' || str[temp_i] == '+')
		temp_i++;
	if (str[temp_i - 1] == '+')
		ret_value = add_tilde_plus(command, i, temp, i_temp);
	else if (str[temp_i - 1] == '-')
		ret_value = add_tilde_hyphen(command, i, temp, i_temp);
	else
		ret_value = add_tilde_home(command, i, temp, i_temp);
	if (ret_value == 0 && (str[temp_i - 1] == '-' || str[temp_i - 1] == '+'))
		(*i) = (*i) + change_val_two(temp_i, temp, i_temp, str);
	else if (ret_value == 0)
		(*i) = (*i) + change_val_one(temp_i, temp, i_temp, str);
}
