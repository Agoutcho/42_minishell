/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/09 17:28:23 by atchougo         ###   ########.fr       */
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

int count_dollar_size(t_command *command, char *str, long *i, int *counter)
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
        return 0;
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
        DEBUG("temp[size_dollar] : %c str[(*i) + size_dollar] : %c", temp[size_dollar], str[(*i) + size_dollar])
    }
    DEBUG("size_dollar : %d", size_dollar)
    *counter = (*counter) + find_lenght_in_env(command, temp);
    (*i) += temp_i - *i - 1;
    DEBUG("*i : %ld", *i);
    free(temp);
    return (1);
}

// void count_dollar_size(t_command *command, char *str, long *i, int *counter)
// {
//     int size_dollar;
//     int temp_i;
//     char *temp;

//     DEBUG("*i : %ld", *i)
//     (*i)++;
//     DEBUG("*i : %ld", *i)
//     if (str[*i] == 0 || str[*i] == ' ')
//     {
//         DEBUG("str[i - 1] : %c str[i] : %c", str[(*i) - 1], str[*i])
//         (*counter)++;
//         return ;
//     }
//     temp_i = *i;
//     while (str[temp_i] && ft_isalnum(str[temp_i]))
//         temp_i++;
//     size_dollar = temp_i - *i + 1;
//     DEBUG("size_dollar : %d", size_dollar)
//     temp = (char *)malloc(sizeof(char) * (size_dollar + 1));
//     if (!temp)
//         big_free(command);
//     temp[size_dollar] = 0;
//     temp[--size_dollar] = '=';
//     while (size_dollar-- > 0)
//     {
//         temp[size_dollar] = str[(*i) + size_dollar];
//         DEBUG("temp[size_dollar] : %c str[(*i) + size_dollar] : %c", temp[size_dollar] , str[(*i) + size_dollar])
//     }
//     DEBUG("size_dollar : %d",size_dollar)
//     *counter = (*counter) + find_lenght_in_env(command, temp);
//     (*i) += temp_i - *i - 1;
//     DEBUG("*i : %ld", *i);
//     free(temp);
// }

// int count_arg_size(t_command *command, char *str, long *i)
// {
//     int counter;

//     counter = 0;
//     while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' 
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

int is_stop_char(t_command *command, char c)
{
    if (command->quote != e_no_quote)
    {
        // DEBUG("c : %d, quote : %d", c, command->quote);
        return (0);
    }
    else if (command->quote == e_no_quote && !is_redir(c) && c != '|' \
        && c != ' ' && c != '\t' && c != '\n' && c != '\r')
    {
        // DEBUG("c : %d", c);
        return (0);
    }
    return (1);
}

int count_arg_size(t_command *command, char *str, long i)
{
    int counter;
    (void)command;

    counter = 0;
    // check_special => '~' 
    while (str[i] && !is_stop_char(command, str[i]))
    {
        // DEBUG("str[%ld] : %c", i, str[i]);
        set_quote(command, &i, 1);
        // DEBUG("str[%ld] : %c", i, str[i]);
        if (str[i] == '$' && command->quote != e_little_quote)
            counter += count_dollar_size(command, str, &i, &counter); // check $- $$ $?  $"" $ 
        else if (command->quote != e_no_quote && str[i] != (char)command->quote)
        {
            // DEBUG()
            i++;
            counter++;
        }
        else if (command->quote == e_no_quote && !is_stop_char(command, str[i]))
        {
            // DEBUG()
            i++;
            counter++;
        }
        // DEBUG("counter : %d", counter)
    }
    return (counter);
}

t_args *add_args(t_command *command, long *i, unsigned long i_cmd, int size)
{
    t_args *temp;
    int arg_size;
    (void)size;

    arg_size = count_arg_size(command, command->input, *i);
    YELLOW
    DEBUG("arg_size : %d", arg_size)
    DEBUG("sizeof(t_args) : %ld", sizeof(t_args))
    temp = (t_args *)malloc(sizeof(t_args));
    if (!temp)
        big_free(command);
    temp->next = NULL;
    temp->arg = add_command(command, command->input, i, arg_size);
    DEBUG("arg : %s", temp->arg);
    if (command->cmd_array[i_cmd].args)
    {
        DEBUG("TEST")
        temp->first = command->cmd_array[i_cmd].args->first;
        command->cmd_array[i_cmd].args->next = temp;
    }
    else
        temp->first = temp;
    RESET
    return (temp);
}

void add_dollar(){}

char *add_command(t_command *command, char *str, long *i, int size)
{
    char *temp;
    long index;

    index = 0;
    temp = (char *)malloc(sizeof(char) * size + 1);
    if (!temp)
        big_free(command);

    while (str[*i] && !is_stop_char(command, str[*i]))
    {
        // DEBUG("str[%ld] : %c", *i, str[*i]);
        set_quote(command, i, 1);
        // DEBUG("str[%ld] : %c", *i, str[*i]);
        if (str[*i] == '$' && command->quote != e_little_quote)
            add_dollar(command, str, &i); // check $- $$ $?  $"" $
        else if (command->quote != e_no_quote && str[*i] != (char)command->quote)
        {
            // DEBUG()
            // add_with_quote();
            while (str[*i] != (char)command->quote)
            {
                // DEBUG("temp[%ld] : %c str[%ld] : %c", index, temp[index], *i, str[*i]);
                temp[index] = str[*i];
                index++;
                (*i)++;
            }
        }
        else if (command->quote == e_no_quote && !is_stop_char(command, str[*i]))
        {
            // DEBUG("temp[%ld] : %c str[%ld] : %c", index, temp[index], *i, str[*i]);
            temp[index] = str[*i];
            index++;
            (*i)++;
        }
    }
    temp[index] = 0;
    return (temp);
}

// PROBLEME avec les quote a la fin "echo" donne echo"
void do_command(t_command *command, unsigned long i_cmd, long *i)
{
    int arg_size;

    arg_size = count_arg_size(command, command->input, *i);
    // DEBUG("arg_size : %d", arg_size)
    if (command->cmd_array[i_cmd].is_cmd_filled == 0)
    {
        // DEBUG("*i : %ld", *i);
        // DEBUG("arg_size : %d", arg_size);
        command->cmd_array[i_cmd].the_cmd = add_command(command, \
            command->input, i, arg_size);
        command->cmd_array[i_cmd].is_cmd_filled = 1;
        // DEBUG("*i : %ld", *i);
    }
    else
    {
        // BLUE
        // while (command->cmd_array[i_cmd].args && command->cmd_array[i_cmd].args->next)
        // {
        //     DEBUG("i_cmd : %ld", i_cmd)
        //     command->cmd_array[i_cmd].args = command->cmd_array[i_cmd].args->next;
        // }
        // DEBUG("arg before %p", command->cmd_array[i_cmd].args)
        command->cmd_array[i_cmd].args = add_args(command, i, i_cmd, arg_size);
        // BLUE
        // DEBUG("arg after  %p", command->cmd_array[i_cmd].args)
        // DEBUG("arg after  %p", command->cmd_array[i_cmd].args->next)
        // RESET
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
    // PURPLE
    // DEBUG("command->cmd.size : %ld", command->size_cmd_array);
    // RESET
    command->quote = e_no_quote;
    command->cmd_array[0].args = NULL;
    while (j < command->size_cmd_array && command->input[i])
    {
        // PURPLE
        // DEBUG("command->input[%ld] : %c", i, command->input[i])
        // DEBUG("command->input[%ld] : %d", i, command->input[i])
        // DEBUG("j : %ld", j)
        // RESET
        if (command->quote == e_no_quote)
            move_space(command->input, &i);
        // PURPLE
        // DEBUG("command->input[%ld] : %c", i, command->input[i])
        // DEBUG("command->input[%ld] : %d", i, command->input[i])
        // DEBUG("j : %ld", j)
        // RESET
        set_quote(command, &i, 0);
        if (command->quote == e_no_quote && command->input[i] == '|')
        {
            j++;
            i++;
        }
        // else if (command->quote == e_no_quote && is_redir(command->input[i]))
        //     do_redirection(command, j, &i);
        else if (command->quote == e_no_quote && command->input[i])
            do_command(command, j, &i);
        // else
        //     do_command_quote(command, j, &i);
    }
}