/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:35:35 by nradal            #+#    #+#             */
/*   Updated: 2023/03/06 10:48:03 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_cmd_utils
{
	char	*path;
	char	**args;
	char	**envp;
}				t_cmd_utils;

t_cmd_utils	prepare_cmd_utils(t_cmd_array *cmd, t_env *env)
{
	t_cmd_utils	cmd_utils;
	char		**env_array;

	cmd_utils.envp = NULL;
	cmd_utils.path = NULL;
	cmd_utils.args = NULL;
	env_array = env_to_array(env);
	if (!env_array)
		return (cmd_utils);
	cmd_utils.path = get_path(cmd->the_cmd, env_array);
	if (!cmd_utils.path)
	{
		ft_putstr_fd(cmd->the_cmd, 2);
		ft_putendl_fd(": command not found", 2);
		free_strs(env_array);
		exit (127);
	}
	cmd_utils.args = add_element_to_array(cmd->args, cmd->the_cmd);
	cmd_utils.envp = env_array;
	return (cmd_utils);
}

int	exec_cmd_utils(t_cmd_utils cmd_utils)
{
	execve(cmd_utils.path, cmd_utils.args, cmd_utils.envp);
	// TODO free un maximum de trucs ici
	// TODO close les pipes_fd
	ft_putstr_fd("Rachele : ", 2);
	perror(cmd_utils.path);
	exit (256);
}

void	commands_handler(t_cmd_array *cmd, t_env *env)
{
	t_cmd_utils	cmd_utils;

	cmd_utils = prepare_cmd_utils(cmd, env);
	if (!cmd_utils.path || !cmd_utils.args || !cmd_utils.envp)
	{
		if (cmd_utils.path)
			free(cmd_utils.path);
		if (cmd_utils.args)
			free_strs(cmd_utils.args);
		if (cmd_utils.envp)
			free_strs(cmd_utils.envp);
		exit (1);
	}
	exec_cmd_utils(cmd_utils);
}

char	**add_element_to_array(char **array, char *element)
{
	int		size;
	int		i;
	char	**new_array;

	size = 0;
	i = 0;
	while (array && array[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	new_array[0] = ft_strdup(element);
	while (i < size)
	{
		new_array[i + 1] = ft_strdup(array[i]);
		i++;
	}
	new_array[size + 1] = NULL;
	return (new_array);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;

	path = get_path_env(env);
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strichr(path, ':'));
		if (!dir)
			return (ft_putendl_fd("Rachele: ft_strndup failed", 2), NULL);
		bin = ft_strcjoin(dir, cmd, '/');
		if (!bin)
			return (ft_putendl_fd("Rachele: ft_strcjoin failed", 2), NULL);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
