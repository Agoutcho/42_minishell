/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/05 16:08:32 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_redir(char c)
{
    if (c == '<' || c == '>')
        return (1);
    else 
        return (0);
}

void do_redirection(t_command *command, unsigned long i_cmd, long *i)
{
    
}

void do_command(t_command *command, unsigned long i_cmd, long *i)
{
    while (command->input[*i])
    {
        if (command->input[*i] == '|' || is_redir(command->input[*i]))
            return ;
        
    } 
}

// command->input est malloc 
// command->env est malloc
// command->cmd.cmd_array est malloc
void init_redir(t_command *command)
{
    long i;
    unsigned long j;

    i = 0;
    j = 0;
    DEBUG("command->cmd.size : %ld", command->size_cmd_array);
    command->quote = e_no_quote;
    while (j < command->size_cmd_array && command->input[i])
    {
        set_quote(command, &i);
        if (command->quote == e_no_quote)
            move_space(command->input, &i);
        if (command->quote == e_no_quote && command->input[i] == '|')
            j++;
        else if (command->quote == e_no_quote && is_redir(command->input[i]))
            do_redirection(command, j, &i);
        else 
            do_command(command, j, &i);
        i++;
    }
}