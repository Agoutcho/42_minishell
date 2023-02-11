/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:40:11 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/09 15:18:48 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char *find_PATH(char **env)
// {
//     int i;
//     char *temp;

//     i = 0;
//     while (env[i])
//     {
//         temp = ft_strnstr(env[i], "PATH", 5);
//         // printf("[%s] temp : %s\n", __FUNCTION__, temp);
//         if (temp)
//             return (env[i]);
//         i++;
//     }
//     return (NULL);
// }

// int main(int argc, char **argv, char **env)
// {
//     if (execve(ft_strjoin("/bin/", argv[1]), &argv[1], env) != 0)
//         printf("Command not found\n");
//     return 0;
// }

void add_i(int *i);

void lolilol(int i)
{
    DEBUG("i avant add : %d", i);
    add_i(&i);
    DEBUG("i apres add : %d", i);
}

void add_i(int *i)
{
    (*i)++;
}

int main(void)
{
    int i;

    i = 500;
    DEBUG("i avant add : %d", i);
    add_i(&i);
    DEBUG("i apres add : %d", i);
    lolilol(i);
    DEBUG("i apres lolilol : %d", i);
}
