/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:03:46 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/13 15:19:50 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// command->input est malloc 
// command->env est malloc
void parsing(t_command *command)
{
    check_parse_error(command);
    init_command(command);
    init_redir(command);
    parsing_input(command);
}