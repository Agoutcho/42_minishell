/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/05 03:32:06 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// command->input est malloc 
// command->env est malloc
// command->cmd.cmd_array est malloc
void init_redir(t_command *command)
{
    long i;
    unsigned long j;

    i = 0;
    j = 0;
    DEBUG("command->cmd.size : %ld", command->cmd.size);
    command->quote = e_no_quote;
    while (j < command->cmd.size && command->input[i])
    {
        set_quote(command, &i);
        if (command->quote == e_no_quote && command->input[i] == '|')
            j++;
        if (command->quote == e_no_quote)
    }
}