/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:03:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 02:06:31 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing(t_data *data)
{
	check_parse_error(data);
	init_command(data);
	init_redir(data);
	parsing_input(data);
	transform_args(data);
}
