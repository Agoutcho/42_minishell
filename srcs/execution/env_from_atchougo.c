/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_atchougo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:09:41 by nradal            #+#    #+#             */
/*   Updated: 2023/02/10 15:09:42 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_printable(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

/**
 * @brief Add a new element in env list at the end 
 * 
 * @param data 
 * @param str The string to add like "var=lol"
 * @return int 
 */
int add_to_env(t_data *data, char *str)
{
    t_env *new;
    t_env *temp;
    int key_len;
    int value_len;

    // DEBUG("data->first key : %s", data->env->first->key);
    temp = data->env;
    // DEBUG("temp->first key : %s", temp->first->key);
    while (temp->next)
        temp = temp->next;
    // DEBUG("last temp->key : %s", temp->key);
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (0);
    new->first = temp->first;
    // DEBUG("new->first key : %s", new->first->key);
    new->next = NULL;
    temp->next = new;
    if (check_printable(str))
    {
        key_len = 0;
        value_len = 0;
        while (str[key_len] != '=')
            key_len++;
        while (str[value_len + key_len])
            value_len++;
        data->env->key = (char *)malloc(sizeof(char) * key_len + 1);
        if (!data->env->key)
            return (0);
        data->env->value = (char *)malloc(sizeof(char) * value_len + 1);
        if (!data->env->value)
            return (0);
        ft_strlcat(data->env->key, str, key_len + 2);
        ft_strlcpy(data->env->value, str + key_len + 1, value_len + 2);
    }
    else
    {
        key_len = 0;
        while (str[key_len])
            key_len++;
        data->env->key = (char *)malloc(sizeof(char) * key_len + 1);
        if (!data->env->key)
            return (0);
        ft_strlcat(data->env->key, str, key_len + 2);
    }
    data->env->affiche_env = check_printable(str);
    return (1);
}

t_env *find_env_value(t_data *data, char *key)
{
    char *temp_key;
    t_env *temp;
    
    temp = data->env->first;
    while (temp->next)
    {
        temp_key = temp->key;
        if (ft_strncmp(temp_key, key, ft_strlen(temp_key) + 1) == 0)
            return (temp);
        temp = temp->next;
    }
    temp_key = temp->key;
    if (ft_strncmp(temp_key, key, ft_strlen(temp_key) + 1) == 0)
        return (temp);
    return (NULL);
}

char *change_shlvl(char *env_value)
{
    char *shlvl;

    //DEBUG("     env_value :  %p", &env_value)
    shlvl = ft_itoa(ft_atoi(env_value) + 1);
    //DEBUG("     shlvl :      %p", &shlvl)
    free(env_value);
    //DEBUG("     env_value :  %p", &env_value)
    //DEBUG("     shlvl :      %p", &shlvl)
    return (shlvl);
}

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
    ft_strlcpy(env->value, envp + key_len + 1, value_len + 2);
    if (ft_strncmp(env->key, "SHLVL=", ft_strlen(env->key) + 1) == 0)
        env->value = change_shlvl(env->value);
    env->affiche_env = 1;
    return (1);
}

int lst_add_back_env(t_data *data, char **env, int j)
{
    t_env *new;
    t_env *temp;

    // DEBUG("data->first key : %s", data->env->first->key);
    temp = data->env;
    // DEBUG("temp->first key : %s", temp->first->key);
    while (temp->next)
        temp = temp->next;
    // DEBUG("last temp->key : %s", temp->key);
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (0);
    new->first = temp->first;
    // DEBUG("new->first key : %s", new->first->key);
    new->next = NULL;
    temp->next = new;
    if (!lst_add_env_value(env[j], new))
        return (0);
    return (1);
}

int copy_env(t_data *data, char **env)
{
    int j;
    t_env *first;
    
    first = (t_env *)malloc(sizeof(t_env));
    if (!first)
        return (0);
    data->env = first;
    data->env->first = first;
    data->env->next = NULL;
    if (!lst_add_env_value(env[0], data->env))
        return (0);
    j = 1;
    while (env[j])
    {
        // DEBUG("------------------")
        // DEBUG("Before add back")
        // DEBUG("env[%d] : %s",j ,env[j])
        // DEBUG("data->env->key : %s", data->env->key)
        // DEBUG("data->env->first->key : %s", data->env->first->key)
        // DEBUG("------------------")
        if (!lst_add_back_env(data, env, j))
            return (0);
        // DEBUG("env[%d] : %s",j ,env[j])
        // DEBUG("------------------")
        // DEBUG("After add back")
        // DEBUG("env[%d] : %s",j ,env[j])
        // DEBUG("data->env->key : %s", data->env->key)
        // DEBUG("data->env->first->key : %s", data->env->first->key)
        // DEBUG("------------------")
        j++;
    }
    return (1);
}

// int create_env(t_data *data)
// {
//     t_env *first;

//     first = NULL;
// }

void	print_list(t_env *env)
{
	t_env *list;

	list = env->first;
    while (list != NULL)
	{
        printf("KEY\t:%s\tVALUE\t:%s\n", list->key, list->value);
        list = list->next;
    }
}

int init_env(t_data *data, char **env)
{
    if (env[0] != NULL && !copy_env(data, env))
        return (0);
    // else if (env[0] == NULL && !create_env(data))
    //     return (0);
    return (1);
}