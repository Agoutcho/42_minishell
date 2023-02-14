/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:40:11 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/14 20:14:07 by atchougo         ###   ########.fr       */
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

int	main(void)
{
	int	i;

	i = 0;
	while (__environ[i])
		DEBUG("%s", __environ[i++]);
}
