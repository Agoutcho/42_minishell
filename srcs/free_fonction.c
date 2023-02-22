/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:56:05 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/22 01:31:04 by atchougo         ###   ########.fr       */
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

void	free_env(t_data *data)
{
	t_env	*temp;

	if (data->env && data->env->first)
		data->env = data->env->first;
	while (data->env)
	{
		temp = data->env;
		secure_char_free(data->env->key);
		secure_char_free(data->env->value);
		data->env = data->env->next;
		free(temp);
		temp = NULL;
	}
}

void	free_heredoc(t_data *data)
{
	t_heredoc	*temp;

	if (data->heredoc && data->heredoc->first)
		data->heredoc = data->heredoc->first;
	while (data->heredoc)
	{
		temp = data->heredoc;
		secure_char_free(data->heredoc->line);
		data->heredoc = data->heredoc->next;
		free(temp);
		temp = NULL;
	}
}

static void	free_redir(t_data *data, long i)
{
	long	j;

	j = 0;
	while (j < data->cmd_array[i].redir_size)
	{
		secure_char_free(data->cmd_array[i].redir_array[j].file_name);
		j++;
	}
	if (data->cmd_array[i].redir_array)
		free(data->cmd_array[i].redir_array);
	data->cmd_array[i].redir_array = NULL;
}

void	free_cmd(t_data *data)
{
	t_args	*targs;
	long	i;

	i = 0;
	while (i < data->size_cmd_array)
	{
		secure_char_free(data->cmd_array[i].the_cmd);
		if (data->cmd_array[i].arg && data->cmd_array[i].arg->first)
			data->cmd_array[i].arg = data->cmd_array[i].arg->first;
		while (data->cmd_array[i].arg)
		{
			targs = data->cmd_array[i].arg;
			secure_char_free(targs->arg);
			data->cmd_array[i].arg = data->cmd_array[i].arg->next;
			free(targs);
			targs = NULL;
		}
		free_redir(data, i);
		i++;
	}
	if (data->cmd_array)
	{
		free(data->cmd_array);
		data->cmd_array = NULL;
	}
}
