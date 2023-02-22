/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:56:05 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:22:23 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	secure_char_free(char *input)
{
	if (input)
	{
		free(input);
		input = NULL;
	}
}

void	free_env(t_data *command)
{
	t_env	*temp;

	if (command->env && command->env->first)
		command->env = command->env->first;
	while (command->env)
	{
		temp = command->env;
		secure_char_free(command->env->key);
		secure_char_free(command->env->value);
		command->env = command->env->next;
		free(temp);
		temp = NULL;
	}
}

void	free_heredoc(t_data *command)
{
	t_heredoc	*temp;

	if (command->heredoc && command->heredoc->first)
		command->heredoc = command->heredoc->first;
	while (command->heredoc)
	{
		temp = command->heredoc;
		secure_char_free(command->heredoc->line);
		command->heredoc = command->heredoc->next;
		free(temp);
		temp = NULL;
	}
}

static void	free_redir(t_data *command, long i)
{
	long	j;

	j = 0;
	while (j < command->cmd_array[i].redir_size)
	{
		secure_char_free(command->cmd_array[i].redir_array[j].file_name);
		j++;
	}
	if (command->cmd_array[i].redir_array)
		free(command->cmd_array[i].redir_array);
	command->cmd_array[i].redir_array = NULL;
}

void	free_cmd(t_data *command)
{
	t_args	*targs;
	long	i;

	i = 0;
	while (i < command->size_cmd_array)
	{
		secure_char_free(command->cmd_array[i].the_cmd);
		if (command->cmd_array[i].args && command->cmd_array[i].args->first)
			command->cmd_array[i].args = command->cmd_array[i].args->first;
		while (command->cmd_array[i].args)
		{
			targs = command->cmd_array[i].args;
			secure_char_free(targs->arg);
			command->cmd_array[i].args = command->cmd_array[i].args->next;
			free(targs);
			targs = NULL;
		}
		free_redir(command, i);
		i++;
	}
	if (command->cmd_array)
	{
		free(command->cmd_array);
		command->cmd_array = NULL;
	}
}
