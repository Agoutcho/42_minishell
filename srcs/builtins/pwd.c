/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:40:08 by nradal            #+#    #+#             */
/*   Updated: 2023/03/08 22:37:16 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd_array *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (printf("lol\n"), set_g_exit_code(1, 1));
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (set_g_exit_code(0, 1));
}
