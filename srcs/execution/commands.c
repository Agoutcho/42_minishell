/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:35:35 by nradal            #+#    #+#             */
/*   Updated: 2023/02/26 16:49:12 by atchougo         ###   ########.fr       */
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
		return (cmd_utils);
	}
	cmd_utils.args = add_element_to_array(cmd->args, cmd->the_cmd);
	cmd_utils.envp = env_array;
	return (cmd_utils);
}

int	exec_cmd_utils(t_cmd_utils cmd_utils)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pid");
		return (0);
	}
	else if (pid == 0)
	{
		execve(cmd_utils.path, cmd_utils.args, cmd_utils.envp);
		perror("execve");
		return (0);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid");
		return (0);
	}
	return (1);
}

int	commands_handler(t_cmd_array *cmd, t_env *env)
{
	t_cmd_utils	cmd_utils;
	int			ret;
	
	cmd_utils = prepare_cmd_utils(cmd, env);
	if (!cmd_utils.path || !cmd_utils.args || !cmd_utils.envp)
	{
		if (cmd_utils.path)
			free(cmd_utils.path);
		if (cmd_utils.args)
			free_strs(cmd_utils.args);
		if (cmd_utils.envp)
			free_strs(cmd_utils.envp);
		return (0);
	}
	ret = exec_cmd_utils(cmd_utils);
	if (cmd_utils.path)
		free(cmd_utils.path);
	if (cmd_utils.args)
	 	free_strs(cmd_utils.args);
	if (cmd_utils.envp)
		free_strs(cmd_utils.envp);
	return (ret);
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
	int		i;

	i = 0;
	if (!env[i])
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path = env[i] + 5;
	while (path && ft_strichr(path, ':') > -1)
	{
		//TODO test malloc
		dir = ft_strndup(path, ft_strichr(path, ':'));
		bin = ft_strcjoin(dir, cmd, '/');
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (NULL);
}
