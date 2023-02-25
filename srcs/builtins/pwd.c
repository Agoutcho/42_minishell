/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:40:08 by nradal            #+#    #+#             */
/*   Updated: 2023/02/24 04:52:28 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;

	if (args && args[0])
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (1);
}
