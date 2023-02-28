/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:40:11 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/28 21:14:02 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
// char *testo(char *test)
// {
//     test = "MDR lol";
//     return (test);
// }

int	main(void)
{
    int fd1 = 1, fd2 = 0;
    fd2 = open("/nfs/homes/atchougo/goinfre", O_RDWR | __O_TMPFILE);
    DEBUG("fd2 : %d", fd2)
    dup2(fd1, fd2);
    write(fd1, "1\n", 2);
    write(fd2, "2\n", 2);
    sleep(10);
    exit(0);
}
