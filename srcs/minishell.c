/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/01/23 21:17:42 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void toutfree(char *input)
{
	if (input)
	{
		free (input);
		input = NULL;
	}
}

/**
 * @brief	Displays the prompt and calls a new function "parsing" which returns an int (ret) and takes input and t_cmd struct as arguments
 */
int	get_input(t_command *command)
{
	char	*input;
	int		ret;

	ret = 1;
	command->input = readline("Rachele ═> ");
	input = command->input;
	if (!input)
	{
		toutfree(input);
		return (0);
	}
	if (!ft_strlen(input))
	{
		toutfree(input);
		return (1);
	}
	if (input && *input && input[0] != ' ')
    	add_history(input);
	// declarer la struct t_cmd + l'init et appeler la fonction de parsing en lui passant la struct.
	toutfree(input);
	return (ret);
}

/**
 * @brief	Handle get_input returns
 */
void	prompt(t_command *command)
{
	int	ret;

	ret = 0;
	while (true)
	{
		ret = get_input(command);
		if (ret == 0)
		{
			printf("CTRL+D = EXIT\n");
			exit(1);// EXIT car ctrl + D
		}
		else 
		{
			
		}
		// else if (ret == ???) Voir apres ce qu'il faudrait rajouter pour gerer tous les cas.
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_command command;
	
	(void)argv;
	if (argc == 1)
	{
		init_term(0);
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, sig_handler);
		command.env = env;
		prompt(&command);
	}
	return (0);
}
