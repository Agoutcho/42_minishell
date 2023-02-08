/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/08 05:27:10 by atchougo         ###   ########.fr       */
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

// void do_redirection(t_command *command, unsigned long i_cmd, long *i)
// {
    
// }

int find_lenght_in_env(t_command *command, char *str)
{
    t_env *temp;

    temp = command->env->first;
    if (!*str)
        return (0);
    while (temp->next)
    {
        DEBUG("key : %s", temp->key);
        if (ft_strncmp(temp->key, str, ft_strlen(str) + 1) == 0)
        {
            DEBUG("value : %s", temp->value)
            DEBUG("len : %zu", ft_strlen(temp->value))
            return (ft_strlen(temp->value));
        }
        temp = temp->next;
    }
    return (0);
}

void count_dollar_size(t_command *command, char *str, long *i, int *counter)
{
    int size_dollar;
    int temp_i;
    char *temp;

    DEBUG("*i : %ld", *i)
    (*i)++;
    DEBUG("*i : %ld", *i)
    if (str[*i] == 0 || str[*i] == ' ')
    {
        DEBUG("str[i - 1] : %c str[i] : %c", str[(*i) - 1], str[*i])
        (*counter)++;
        return ;
    }
    temp_i = *i;
    while (str[temp_i] && ft_isalnum(str[temp_i]))
        temp_i++;
    size_dollar = temp_i - *i + 1;
    DEBUG("size_dollar : %d", size_dollar)
    temp = (char *)malloc(sizeof(char) * (size_dollar + 1));
    if (!temp)
        big_free(command);
    temp[size_dollar] = 0;
    temp[--size_dollar] = '=';
    while (size_dollar-- > 0)
    {
        temp[size_dollar] = str[(*i) + size_dollar];
        DEBUG("temp[size_dollar] : %c str[(*i) + size_dollar] : %c", temp[size_dollar] , str[(*i) + size_dollar])
    }
    DEBUG("size_dollar : %d",size_dollar)
    *counter = (*counter) + find_lenght_in_env(command, temp);
    (*i) += temp_i - *i - 1;
    DEBUG("*i : %ld", *i);
    free(temp);
}

// int count_arg_size(t_command *command, char *str, long *i)
// {
//     int counter;

//     counter = 0;
//     while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' \
//         && str[*i] != ' ')
//     {
//         DEBUG("str[%ld] : %c", *i, str[*i]);
//         if (str[*i] == '$')
//             count_dollar_size(command, str, i, &counter);
//         else
//             counter++;
//         DEBUG("TEST");
//         (*i)++;
//     }
//     DEBUG("TEST");
//     return (counter);
// }

int count_arg_size(t_command *command, char *str, long *i)
{
    int counter;

    counter = 0;
    while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' \
        && str[*i] != ' ')
    {
        DEBUG("str[%ld] : %c", *i, str[*i]);
            counter++;
        DEBUG("TEST");
    }
    DEBUG("TEST");
    return (counter);
}

char *add_command(t_command *command, char *str, long *i, int size)
{
    char *temp;
    int index;

    index = 0;
    temp = (char *)malloc(sizeof(char) * size + 1);
    if (!temp)
        big_free(command);
    while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' \
        && str[*i] != ' ')
    {
        DEBUG("str[%ld] : %c", *i, str[*i]);
        temp[index] = str[*i];
        index++;
        (*i)++;
        DEBUG("TEST");
    } 
    temp[index] = 0;
    return (temp);
}

void do_command(t_command *command, unsigned long i_cmd, long *i)
{
    int arg_size;
    (void)i_cmd;

    while (command->input[*i])
    {
        if (command->cmd_array[i_cmd].is_cmd_filled == 0)
        {
            DEBUG("*i : %ld", *i);
            arg_size = count_arg_size(command, command->input, i);
            DEBUG("arg_size : %d", arg_size);
            command->cmd_array[i_cmd].the_cmd = add_command(command, \
                command->input, i, arg_size);
            command->cmd_array[i_cmd].is_cmd_filled = 1;
            DEBUG("*i : %ld", *i);
        }
        else
        {
            
        }
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
        DEBUG("command->input[%ld] : %c", i, command->input[i])
        DEBUG("j : %ld", j)
        set_quote(command, &i);
        if (command->quote == e_no_quote)
            move_space(command->input, &i);
        if (command->quote == e_no_quote && command->input[i] == '|')
        {
            j++;
            i++;
        }
        // else if (command->quote == e_no_quote && is_redir(command->input[i]))
        //     do_redirection(command, j, &i);
        else if (command->quote == e_no_quote)
            do_command(command, j, &i);
        // else
        //     do_command_quote(command, j, &i);
        i++;
    }
}