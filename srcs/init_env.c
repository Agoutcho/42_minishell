/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:29:00 by nradal            #+#    #+#             */
/*   Updated: 2023/01/20 17:58:42 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int lst_add_env_value(char *envp, t_env *env)
{
    int key_len;
    int value_len;

    key_len = 0;
    value_len = 0;
    if (!envp)
        return (0);
    while (envp[key_len] != '=')
        key_len++;
    while (envp[value_len + key_len])
        value_len++;
    env->key = (char *)malloc(sizeof(char) * key_len + 1);
    if (!env->key)
        return (0);
    env->value = (char *)malloc(sizeof(char) * value_len + 1);
    if (!env->value)
        return (0);
    ft_strlcat(env->key, envp, key_len + 2);
    ft_strlcat(env->value, envp + key_len + 1, value_len + 2);
    return (1);
}

int init_env(t_command *command, char **env)
{
    int j;
    t_env *first;
    t_env *new;

    (void)command;
    j = 0;
    if (env[j] != NULL)
    {
        first = (t_env *)malloc(sizeof(t_env));
        if (!first)
            return (0);
        command->env = first;
        command->env->first = first;
        command->env->next = NULL;
        if (!lst_add_env_value(env[j], command->env))
            return (0);
        j++;
        while (env[j])
        {
            new = (t_env *)malloc(sizeof(t_env));
            if (!new)
                return (0);
            new->first = first;
            new->next = NULL;
            command->env->next = new;
            command->env = new;
            if (!lst_add_env_value(env[j], command->env))
                return (0);
            DEBUG("enj[%d] : %s", j, env[j])
            DEBUG("key : %s", command->env->key)
            DEBUG("value : %s", command->env->value)
            j++;
        }
        command->env = first;
    }
    return (1);
}