/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:35 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/13 16:06:19 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_redir(t_command *command)
{
    long i;
    int counter_redir;

    i = 0;
    counter_redir = 0;
    command->quote = e_no_quote;
    while (command->input[i])
    {
        set_quote(command, &i, 1);
        if (command->quote == e_no_quote && command->input[i] == '|')
            counter_redir++;
        i++;
    }
    
}