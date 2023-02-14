/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/14 04:53:09 by atchougo         ###   ########.fr       */
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


// echo "xD > file" >> $SHELL | cat -e lol > file.txt >> $SHELL segfault
void affiche(t_command *command)
{
	unsigned long i;
	unsigned long j;

	j = 0;
	i = 0;
	DEBUG("\033[0;31m---------[AFFICHAGE]-----------\033[0m")
	DEBUG("nombre de commande : %ld", command->size_cmd_array)
	while (i < command->size_cmd_array)
	{
		DEBUG("-----------------------------------")
		DEBUG("Commande : %ld", i + 1)
		if (command->cmd_array[i].args)
			command->cmd_array[i].args = command->cmd_array[i].args->first;
		CYAN
		DEBUG("command : |%s|", command->cmd_array[i].the_cmd)
		RESET
		DEBUG("nombre de redirection : %ld", command->cmd_array[i].redir_size)
		while (j < command->cmd_array[i].redir_size)
		{
			GREEN
			DEBUG("j : %ld", j)
			DEBUG("type : %d", command->cmd_array[i].redir_array[j].type)
			DEBUG("file : %s", command->cmd_array[i].redir_array[j].file_name)
			RESET
			j++;
		}
		j = 0;
		while (command->cmd_array[i].args)
		{
			YELLOW
			DEBUG("arg : |%s|", command->cmd_array[i].args->arg)
			command->cmd_array[i].args = command->cmd_array[i].args->next;
			RESET
		}
		i++;
	}
}

/**
 * @brief	Displays the prompt and calls a new function "parsing" which returns an int (ret) and takes input and t_cmd struct as arguments
 */
int	get_input(t_command *command)
{
	command->i_input = 0;
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
	DEBUG("%s", command->input);
	parsing(command);
	affiche(command);
	// DEBUG("command : |%s|", command->cmd_array[0].the_cmd)
	// DEBUG("arg : |%s|", command->cmd_array[0].args->first->arg)
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
	// t_env *temp;
	// char **envp;
	
	(void)env;
	(void)argv;
	g_exit_code = 0;
	YELLOW
	printf("\n|------------------------------------------------------------|\n");
	printf("\n|------------------------MINISHELL---------------------------|\n");
	printf("\n|------------------------------------------------------------|\n\n");
	RESET
	if (argc == 1)
	{
		// envp = env;
		init_term(0);
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, sig_handler);
		DEBUG("INIT ENV");
		init_env(&command, environ); // utiliser __environ au lieu de envp ou env
		// temp = find_env_value(&command, "PATH=");
		// DEBUG("PATH=%s",temp->value)
		prompt(&command);
	}
	return (0);
}
