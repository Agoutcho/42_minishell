/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:15:24 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/05 03:29:08 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_cmd_filled(t_command *command)
{
    unsigned long i;

    i = 0;
    while (i < command->size_cmd_array)
    {
        command->cmd_array[i].is_cmd_filled = 0;
        i++;
    }
}

void set_quote(t_command *command, long *i, int change_i)
{
    // DEBUG();
    int previous_quote;

    previous_quote = command->quote;
    if (command->input[*i] == '"' && command->quote == e_no_quote)
        command->quote = e_big_quote;
    else if (command->input[*i] == '"' && command->quote == e_big_quote)
        command->quote = e_no_quote;
    if (command->input[*i] == '\'' && command->quote == e_no_quote)
        command->quote = e_little_quote;
    else if (command->input[*i] == '\'' && command->quote == e_little_quote)
        command->quote = e_no_quote;
    if(change_i && previous_quote != (int)command->quote \
        && command->input[(*i) + 1])
        (*i)++;
}

// command->input est malloc 
// command->env est malloc
void init_command(t_command *command)
{
    long i;
    int counter_command;
    t_cmd_array *temp;

    i = 0;
    counter_command = 1;
    command->quote = e_no_quote;
    while (command->input[i])
    {
        set_quote(command, &i, 1);
        if (command->quote == e_no_quote && command->input[i] == '|')
            counter_command++;
        i++;
    }
    command->size_cmd_array = counter_command;
    temp = (t_cmd_array *)malloc(sizeof(t_cmd_array) * counter_command);
    command->cmd_array = temp;
    init_cmd_filled(command);
    DEBUG("counter : %d", counter_command)
}