/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:29:02 by nradal            #+#    #+#             */
/*   Updated: 2023/02/14 20:16:22 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	The function uses the "mode" parameter to determine if it should enable or
 * 			disable the canonical input (ICANON) and display of control characters (ECHOCTL)
 * 			for the terminal.
 *
 * @param term	Termios struct.
 * @param mode	1 enable.
 * 				0 disable.
 */
void	set_term(struct termios *term, bool mode)
{
	if (mode == 1)
		term->c_lflag |= (ICANON | ECHOCTL);
	else
		term->c_lflag &= ~(ICANON | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

/**
 * @brief	The function initializes the terminal by getting the attributes of the terminal using tcgetattr.
 * @param mode	1 enable.
 * 				0 disable.
 */
void	init_term(bool mode)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &term) == 0)
		{
			set_term(&term, mode);
		}
		else
		{
			// Error handler
			printf("tcgetattr unable to initialize terminal\n");
			exit(1);
		}
	}
	else
	{
		// Error handler
		printf("fd(0) isn't associated with a terminal\n");
		exit(1);
	}
}
