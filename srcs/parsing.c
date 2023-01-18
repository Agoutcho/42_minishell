/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:20:57 by nradal            #+#    #+#             */
/*   Updated: 2023/01/17 23:22:38 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	line = readline("prompt> ");
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
		int i = 0;
		while (input[i] != NULL)
		{
			printf("\t(Affichage) %s\n", input[i]);
			i++;
		}
	}
}