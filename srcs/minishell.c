/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/04 18:40:44 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tout_free(char *input)
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
	command->input = readline("Rachele ═> ");
	if (!command->input)
	{
		tout_free(command->input);
		return (0);
	}
	if (!ft_strlen(command->input))
	{
		tout_free(command->input);
		return (1);
	}
	if (command->input && *command->input && command->input[0] != ' ')
    	add_history(command->input);
	parsing(command);
	tout_free(command->input);
	return (1);
}

void big_free(t_command *command)
{
	t_env *temp;

	command->env = command->env->first;
	while (command->env->next)
	{
		temp = command->env;
		tout_free(command->env->key);
		tout_free(command->env->value);
		command->env = command->env->next;
		free (temp);
	}
	temp = command->env;
	tout_free(command->env->key);
	tout_free(command->env->value);
	command->env = command->env->next;
	free (temp);
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
			big_free(command);
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
	t_env *temp;
	char **envp;
	
	(void)env;
	(void)argv;
	if (argc == 1)
	{
		envp = env;
		init_term(0);
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, sig_handler);
		DEBUG("INIT ENV");
		init_env(&command, envp);
		temp = find_env_value(&command, "PATH=");
		DEBUG("PATH=%s",temp->value)
		prompt(&command);
	}
	return (0);
}
