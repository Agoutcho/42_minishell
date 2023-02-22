/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/22 01:33:50 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_to_zero(t_data *data);

// echo "xD > file" >> $SHELL | cat -e lol > file.txt >> $SHELL segfault
void	affiche(t_data *data)
{
	t_args			*targs;
	long	i;
	long	j;

	j = 0;
	i = 0;
	DEBUG("\033[0;31m---------[AFFICHAGE]-----------\033[0m")
		DEBUG("nombre de commande : %ld", data->size_cmd_array)
		while (i < data->size_cmd_array)
		{
			DEBUG("-----------------------------------")
				DEBUG("Commande : %ld", i + 1)
				if (data->cmd_array[i].arg)
					targs = data->cmd_array[i].arg->first;
			CYAN
				DEBUG("data : |%s|", data->cmd_array[i].the_cmd)
				RESET
				DEBUG("nombre de redirection : %ld", data->cmd_array[i].redir_size)
				while (j < data->cmd_array[i].redir_size)
				{
					GREEN;
						DEBUG("j : %ld", j)
						DEBUG("type : %d", data->cmd_array[i].redir_array[j].type)
						DEBUG("file : %s", data->cmd_array[i].redir_array[j].file_name)
						RESET
						j++;
				}
			j = 0;
			while (targs)
			{
				YELLOW
					DEBUG("arg : |%s|", data->cmd_array[i].arg->arg)
					targs = targs->next;
				RESET
			}
			i++;
		}
}

/**
 * @brief	Displays the prompt and calls a new function "parsing" which returns an int (ret) and takes input and t_cmd struct as arguments
 */
int	get_input(t_data *data)
{
	data->i_input = 0;
	data->input = readline("Rachele ═> ");
	if (!data->input)
	{
		secure_char_free(data->input);
		return (0);
	}
	if (!ft_strlen(data->input))
	{
		secure_char_free(data->input);
		return (1);
	}
	if (data->input && *data->input && data->input[0] != ' ')
		add_history(data->input);
	DEBUG("%s", data->input);
	parsing(data);
	// affiche(data);
	secure_char_free(data->input);
	free_cmd(data);
	init_to_zero(data);
	return (1);
}

void	big_free(t_data *data)
{
	free_env(data);
	free_cmd(data);
}

/**
 * @brief	Handle get_input returns
 */
void	prompt(t_data *data)
{
	int	ret;

	ret = 0;
	while (true)
	{
		ret = get_input(data);
		if (ret == 0)
		{
			printf("CTRL+D = EXIT\n");
			big_free(data);
			exit(1);// EXIT car ctrl + D
		}
	}
	return ;
}

void init_to_zero(t_data *data)
{
	data->size_cmd_array = 0;
	data->cmd_array = NULL;
	// data->env = NULL;
	data->input = NULL;
}

// TODO add HEREDOC
int	main(int argc, char **argv)
{
	t_data data;
	(void)argv;
	
	g_exit_code = 0;
	if (argc == 1)
	{
		init_term(0);
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, sig_handler);
		init_env(&data, environ);
		prompt(&data);
		/** HEREDOC */
		// fill_heredoc(&data, "heredoc");
		// if (data.heredoc)
		// 	data.heredoc = data.heredoc->first;
		// while (data.heredoc)
		// {
		// 	DEBUG("heredoc : %s", data.heredoc->line);
		// 	data.heredoc = data.heredoc->next;
		// }
	}
	return (0);
}
