/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/02/26 21:14:30 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_to_zero(t_data *data, int env_to_null);
// int	g_exit_code;
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
				if (data->cmd[i].arg)
					targs = data->cmd[i].arg->first;
			CYAN
				DEBUG("data : |%s|", data->cmd[i].the_cmd)
				RESET
				DEBUG("nombre de redirection : %ld", data->cmd[i].redir_size)
				while (j < data->cmd[i].redir_size)
				{
					GREEN;
						DEBUG("j : %ld", j)
						DEBUG("type : %d", data->cmd[i].redir_array[j].type)
						DEBUG("file : %s", data->cmd[i].redir_array[j].file_name)
						RESET
						j++;
				}
			j = 0;
			while (targs)
			{
				YELLOW
					DEBUG("arg : |%s|", data->cmd[i].arg->arg)
					targs = targs->next;
				RESET
			}
			i++;
		}
}

int	set_g_exit_code(int code, int return_value)
{
	g_exit_code = code;
	return (return_value);
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
	parsing(data);
	secure_char_free(data->input);
	return (2);
}

void	big_free(t_data *data)
{
	free_env(data);
	free_cmd(data);
	rl_clear_history();
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
			ft_putstr_fd("exit\n", 1);
			big_free(data);
			exit(g_exit_code);
		}
		if (ret == 1)
			continue;
		data->fd_saver.stdin = dup(0);
		data->fd_saver.stdout = dup(1);
		data->fd_saver.stderr = dup(2);
		if (!execution(data))
		{
			big_free(data);
			exit(1);
		}
		close(data->fd_saver.stdin);
		close(data->fd_saver.stdout);
		close(data->fd_saver.stderr);
		free_cmd(data);
		init_to_zero(data, 0);
	}
	return ;
}

void init_to_zero(t_data *data, int env_to_null)
{
	data->size_cmd_array = 0;
	data->cmd = NULL;
	data->input = NULL;
	if (env_to_null)
		data->env = NULL;
}

int	main(int argc, char **argv)
{
	t_data data;
	(void)argv;

	g_exit_code = 0;
	init_to_zero(&data, 1);
	if (argc == 1)
	{
		init_term(0);
		signal(SIGINT, sig_handler);
		// signal(SIGQUIT, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		if (!init_env(&data, environ))
		{
			big_free(&data);
			exit(1);
		}
		prompt(&data);
	}
	return (0);
}
