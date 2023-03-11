/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:40:08 by nradal            #+#    #+#             */
/*   Updated: 2023/03/11 22:17:15 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_env_pwd(t_env *env)
{
	t_env	*temp;
	temp = search_key("PWD=", env);
	if (temp)
	{
		ft_putendl_fd(temp->value, STDOUT_FILENO);
		g_exit_code = 0;
	}
	else
	{
		ft_putendl_fd("Rachele : pwd: no pwd set", STDERR_FILENO);
		g_exit_code = 1;
	}
	env = env->first;
}

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_env_pwd(env);
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (set_g_exit_code(0, 1));
}