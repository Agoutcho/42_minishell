/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:03:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 05:51:35 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing(t_data *data)
{
	if (!check_parse_error(data))
		return (0);
	init_command(data);
	init_redir(data);
	parsing_input(data);
	transform_args(data);
	return (1);
}
