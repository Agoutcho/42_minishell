/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:40:11 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/24 04:45:48 by atchougo         ###   ########.fr       */
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

// int fd;

// int	main(int ac, char ** ag, char ** e)
// {
//     pid_t   pid;
//     int fd = open("outfile", O_RDWR | O_CREAT, 0777);
//     char **test =NULL;
//     // printf("parent fd : %d\n",fd);
//     pid = fork();
//     if (pid == 0)
//     {
//         // printf("enfant fd : %d\n",fd);
//         // write(fd, "IK\n", 3);
//         // sleep (20);
//         execve("/bin/ls", test, e);
//         exit(0);
//     }
//     waitpid(pid, NULL, 0);
//     // printf("parent post wait fd : %d\n",fd);
//     // if (write(fd, "OK\n", 3) == -1)
//     //     write(2, "NO\n", 3);
//     // else
//     //     write(2, "YE\n", 3);
//     // sleep(10);
//     close(fd);
//     exit(0);
// }

