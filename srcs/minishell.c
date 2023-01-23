/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:18:40 by nradal            #+#    #+#             */
/*   Updated: 2023/01/18 21:12:53 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)sig;
	printf("[%s]\n", __FUNCTION__);
	printf("\n");
	prompt_and_read();
}

int main(int argc, char **argv, char **env)
{
	struct sigaction	act;
	
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_signal_handler;
	if (sigaction(SIGINT, &act, NULL) == -1)
		exit(EXIT_FAILURE);
	parsing(argc, argv, env);
	return (0);
}