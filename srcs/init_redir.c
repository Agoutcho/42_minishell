/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:35 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/17 20:53:02 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir(char c)
{
    if (c == '<' || c == '>')
        return (1);
    else 
        return (0);
}

void	init_redir(t_command *command)
{
    long	i;
    int		j;
    int		counter_redir;

    i = 0;
    j = 0;
    counter_redir = 0;
    command->cmd_array[j].redir_size = 0;
    command->quote = e_no_quote;
    while (command->input[i])
    {
        set_quote(command, &i, 1);
        if (command->input[i] && command->quote == e_no_quote && is_redir(command->input[i]))
            counter_redir++;
        if (command->input[i] && command->quote == e_no_quote && command->input[i] == '|')
        {
            command->cmd_array[j].redir_size = counter_redir;
            command->cmd_array[j].redir_array = \
            (t_redirect *)malloc(sizeof(t_redirect) * counter_redir);
            counter_redir = 0;
            j++;
        }
        if ((command->input[i] == '<' || command->input[i] == '>') \
            && (command->input[i + 1] == '<' || command->input[i + 1] == '>'))
            i++;
        if (command->input[i])
            i++;
    }
    command->cmd_array[j].redir_size = counter_redir;
    command->cmd_array[j].redir_array = \
    (t_redirect *)malloc(sizeof(t_redirect) * counter_redir);
}
