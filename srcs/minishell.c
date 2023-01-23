/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/01/23 17:40:00 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	Displays the prompt and calls a new function "parsing" which returns an int (ret) and takes input and t_cmd struct as arguments
 */
int	get_input(void)
{
	char	*input;
	int		ret;

	ret = 1;
	input = readline("prompt >");
	if (!input)
		return (0);
	if (!ft_strlen(input))
		return (1);
	// declarer la struct t_cmd + l'init et appeler la fonction de parsing en lui passant la struct.
	return (ret);
}

/**
 * @brief	Handle get_input returns
 */
void	prompt(void)
{
	int	ret;

	ret = 0;
	while (true)
	{
		ret = get_input();
		if (ret == 0)
		{
			printf("CTRL+D = EXIT\n");
			exit(1);// EXIT car ctrl + D
		}
		// else if (ret == ???) Voir apres ce qu'il faudrait rajouter pour gerer tous les cas.
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		init_term(0);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		prompt();
	}
	return (0);
}
