/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:20:57 by nradal            #+#    #+#             */
/*   Updated: 2023/01/18 21:13:58 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

// char	*get_path(char *cmd, char **env) // verifie qu'il existe un path/cmd.	{oui = return path, non = null}
// {
// 	char	*path;
// 	char	*dir;
// 	char	*bin;
// 	int		i;

// 	i = 0;
// 	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
// 		i++;
// 	if (!env[i])
// 		return (NULL);
// 	path = env[i] + 5;
// 	while (path && ft_strichr(path, ':') > -1)
// 	{
// 		dir = ft_strndup(path, ft_strichr(path, ':'));
// 		bin = ft_strcjoin(dir, cmd, '/');
// 		free(dir);
// 		if (access(bin, F_OK) == 0)
// 			return (bin);
// 		free(bin);
// 		path += ft_strichr(path, ':') + 1;
// 	}
// 	return (NULL);
// }

char	**prompt_and_read(void) // lit une ligne de l'entrée standard et la divise en mots séparés par des espaces.
{
	char	*line;

	printf("[%s]\n", __FUNCTION__);
	printf("prompt> ");
	line = readline(NULL);
	// printf("[%s] line %%p : %p\n", __FUNCTION__, line);
	// if (line == NULL)
	// 	exit(0);	
	// printf("[%s] line s : %s, size : %zu\n", __FUNCTION__, line, ft_strlen(line));
	// printf("[%s] line d[0] : %d, d[1] : %d, d[2] : %d, d[3] : %d\n", __FUNCTION__, line[0], line[1], line[2], line[3]);
	if (line != NULL)
		return (ft_split(line, ' '));
	else
	{
		free(line);
		return (NULL);
	}
}

void parsing(int argc, char **argv, char **env)
{
	char		**input;

	(void)argc;
	(void)argv;
	(void)env;
	while ((input = prompt_and_read()) != NULL)
	{
		// Affichage
		// int i = 0;
		// printf("[%s]\n", __FUNCTION__);
		// while (env[i] != NULL)
		// {
		// 	printf("\t(Affichage) %s\n", env[i]);
		// 	i++;
		// }
	}
}