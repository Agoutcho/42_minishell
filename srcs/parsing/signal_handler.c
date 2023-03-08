/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:34 by nradal            #+#    #+#             */
/*   Updated: 2023/03/08 23:46:09 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief This function is used to handle unix signals in main process
 *
 * @param sig Received signal code to handle
 */
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (write(1, "\n", 1) == -1)
			return ;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
		return ;
	}
	if (sig == SIGQUIT)
	{
		// rl_on_new_line();
		// rl_redisplay();
		return ;
	}
	return ;
}


////////////

void	sig_int_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int_child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = -1;
		close (STDIN_FILENO);
		rl_redisplay();
	}
}

void	sig_quit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		// g_exit_code = 131;
	}
}

void	null_signal(int signum)
{
	(void)signum;
}

void	sig_int_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
