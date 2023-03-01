/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:41:35 by nradal            #+#    #+#             */
/*   Updated: 2023/03/01 13:33:46 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipe(t_data *data, int i)
{
	if (pipe(data->cmd[i].pipe_fd) == -1)
    {
        perror("Rachele: pipe:");
        return (0);
    }
    return (1);
}

int ft_connect_pipe(t_data, int i)
{
    if (i >= 1 && data->cmd[i].pipe_fd[0] != -1) // si c'est pas le premier pipe et que pipe_fd[0] est pas fail
    {
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
        {
            perror("Rachele: dup2:");
            return (0);
        }
    }
    else
    {
        if (close(pipe_fd[0] == -1))
        {
            perror("Rachele: close:");
            return (0);
        }
    }
    if (i <= data->size_cmd_array - 1 && data->cmd[i].pipe_fd[1] != -1) // si c'est pas le dernier pipe et que pipe_fd[0] est pas fail
    {
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("Rachele: dup2:");
            return (0);
        }
    }
    else
    {
        if (close(pipe_fd[0]) == -1)
        {
            perror("Rachele: close:");
            return (0);    
        }
    }
    return (1);
}

ft_close_child_fd(t_data *data, int i)
{
    int counter;

    counter = 0;
    while(counter < data->size_cmd_array)
    {
        if (counter != i)
        {
            if (close(data->cmd[counter].pipe_fd[0]) == -1 || close(data->cmd[counter].pipe_fd) == -1)
            {
                perror("Rachele: close:");
                return (0);
            }
        }
        counter++;
    }
}