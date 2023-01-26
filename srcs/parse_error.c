/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/27 00:00:49 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_quotes(t_command *command)
{
    int i;

    i = 0;
    while (command->input[i])
    {
        if (command->input[i] == '"' && command->quote == no_quote)
            command->quote = big_quote;
        else if (command->input[i] == '"' && command->quote == big_quote)
            command->quote = no_quote;
        if (command->input[i] == '\'' && command->quote == no_quote)
            command->quote = little_quote;
        else if (command->input[i] == '\'' && command->quote == little_quote)
            command->quote = no_quote;
        i++;
    }
    if (command->quote == big_quote)
    {
        free(command->input);
        ft_fprintf(STDERR_FILENO ,"Rachele: syntax error near unexpected token `\"'\n");
        exit(128);
    }
    if (command->quote == little_quote)
    {
        free(command->input);
        ft_fprintf(STDERR_FILENO ,"Rachele: syntax error near unexpected token `''\n");
        exit(128);
    }
}

int move_space(char *str, int i)
{
    while (str[i] && str[i] == ' ')
        i++;
    if (!str[i])
        return (-1);
    return (i);
}

void check_parse_error(t_command *command)
{
    int i;

    i = 0;
    command->quote = no_quote;
    check_quotes(command);
    // while (command->input[i])
    // {
    //     if ((i = move_space(command->input, i)) == -1)
    //         return ;
    //     // if (!is_quotes_ok(command->input, i))
    //     // {
    //     //     free(command->input);
    //     //     ft_fprintf(2 ,"Rachele: syntax error near unexpected token `;;'\n");
    //     //     exit(128);
    //     // }
    // }
}