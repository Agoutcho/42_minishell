/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:34:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/28 05:11:52 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_last_value_ok(char *str, int i)
{
    int fd;

    fd = STDERR_FILENO;
    while (i-- > 0 && str[i])
    {
        if (str[i] == '|')
        {
            ft_putstr_fd("Rachele: syntax error: unexpected end of file\n", fd);
            return (0);
        }
        else if (str[i] == '<' || str[i] == '>')
        {
            ft_putstr_fd("Rachele: syntax error near ", fd);
            ft_putstr_fd("unexpected token `newline'\n", fd);
            return (0);
        }
        else if (str[i] != ' ')
            return (1);
    }
    return (1);
}

// command->input est malloc 
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
        ft_putstr_fd("Rachele: unexpected EOF while looking for matching `\"'\n", STDERR_FILENO);
        ft_putstr_fd("Rachele: syntax error: unexpected end of file\n", STDERR_FILENO);
        exit(2);
    }
    if (command->quote == little_quote)
    {
        free(command->input);
        ft_putstr_fd("Rachele: unexpected EOF while looking for matching `''\n", STDERR_FILENO);
        ft_putstr_fd("Rachele: syntax error: unexpected end of file\n", STDERR_FILENO);
        exit(2);
    }
    if (!is_last_value_ok(command->input, i))
    {
        free(command->input);
        exit(2);
    }
}

long move_space(char *str, long *i)
{
    while (str[*i] && str[*i] == ' ')
        (*i)++;
    if (!str[*i])
        return (-1);
    return (*i);
}

void exit_error(char c, char *input)
{
    free(input);
    ft_putstr_fd("Rachele: syntax error near unexpected token `", STDERR_FILENO);
    ft_putchar_fd(c, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
    exit(2);
}

int is_redir_ok(char *str, long i)
{
    if (str[i] != '>' && str[i] != '<')
        return (1);
    if (str[i] == '>' && str[i + 1] != '>')
    {
        i++;
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            exit_error(str[i], str);
    }
    else if (str[i] == '<' && str[i + 1] != '<')
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            exit_error(str[i], str);
    }
    else
    {
        i += 2;
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
            exit_error(str[i], str);
    }
    return (1);
}

void check_redir(t_command *command)
{
    long i;

    i = 0;
    command->quote = no_quote;
    while (command->input[i])
    {
        if (command->quote == no_quote && is_redir_ok(command->input, i))
            i++;
        i++;
    }
}

// command->input est malloc
void check_parse_error(t_command *command)
{
    long i;

    i = 0;
    command->quote = no_quote;
    check_redir(command);
    check_quotes(command);
    if (move_space(command->input, &i) == -1)
        return ;
    if (command->input[i] == '|')
    {
        free(command->input);
        ft_putstr_fd("Rachele: syntax error near unexpected token `|'\n", STDERR_FILENO);
        exit(2);
    }
}