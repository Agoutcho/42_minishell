/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:46:07 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 14:07:44 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_heredoc(t_heredoc *heredoc)
{
	if (heredoc)
	{
		free_heredoc(heredoc->next);
		free(heredoc->line);
		free(heredoc);
	}
}

void	free_redirect(t_redirect *redirect)
{
	if (redirect)
	{
		free(redirect->file_name);
		free_heredoc(redirect->heredoc);
		free(redirect);
	}
}

void	free_cmd_array(t_cmd_array *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i].the_cmd)
	{
		free(cmd[i].the_cmd);
		if (cmd[i].args)
		{
			while (cmd[i].args[j])
				free(cmd[i].args[j++]);
			free(cmd[i].args);
		}
		j = 0;
		while (j < cmd[i].redir_size)
			free_redirect(&cmd[i].redir_array[j++]);
		free(cmd[i].redir_array);
		free(cmd);
		i++;
	}
}

void	tout_free(char *input)
{
	if (input)
	{
		free (input);
		input = NULL;
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	if (env)
		env = env->first;
	while (env)
	{
		temp = env;
		tout_free(env->key);
		tout_free(env->value);
		env = env->next;
		free (temp);
		temp = NULL;
	}
}
