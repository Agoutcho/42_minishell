/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:11:16 by nradal            #+#    #+#             */
/*   Updated: 2023/03/01 15:45:45 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipe(t_data *data, int i)
{
	if (pipe(data->cmd[i].pipe_fd) == -1)
    {
        perror("1Rachele: pipe:");
        return (0);
    }
    return (1);
}

int ft_connect_pipe(t_data *data, int i)
{
    if (data->size_cmd_array == 1)
        return (1);
	if (i == 0)
	{
        close(data->cmd[i].pipe_fd[0]);
        dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO);
    }
	else if (i + 1 == data->size_cmd_array)
	{
        dup2(data->cmd[i - 1].pipe_fd[0], STDIN_FILENO);
        close(data->cmd[i].pipe_fd[0]);
        close(data->cmd[i].pipe_fd[1]);
    }
	else
	{
        close(data->cmd[i].pipe_fd[0]);
        dup2(data->cmd[i - 1].pipe_fd[0], STDIN_FILENO);
        dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO);
    }
    return (1);
}

int ft_close_pipe(t_data *data, int i)
{
	if (data->cmd[i].pipe_fd[0] != -1)
	{
		if (close(data->cmd[i].pipe_fd[0]) == -1)
		{
			perror("6Rachele: close");
			return (0);
		}
	}
	if (data->cmd[i].pipe_fd[1] != -1)
	{
		if (close(data->cmd[i].pipe_fd[1]) == -1)
		{
			perror("7Rachele: close");
			return (0);
		}
	}
	return (1);
}

int ft_close_child_fd(t_data *data, int i)
{
    int counter;

    counter = 0;
    while(counter < data->size_cmd_array)
    {
        if (counter != i && counter != i + 1)
        {
			if (!ft_close_pipe(data, counter))
				return (0);
            // if (close(data->cmd[counter].pipe_fd[0]) == -1 || close(data->cmd[counter].pipe_fd[1]) == -1)
            // {
            //     perror("5bis Rachele: close:");
            //     return (0);
            // }
        }
        counter++;
    }
}

//OLDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
// int	create_pipe(t_data *data, int i)
// {
// 	if (pipe(data->cmd[i].pipe_fd) == -1)
//     {
//         perror("1Rachele: pipe:");
//         return (0);
//     }
//     return (1);
// }

// int ft_connect_pipe(t_data *data, int i)
// {
// 	if (data->size_cmd_array == 1)
// 	{
// 		return (1);
// 	}
//     if (i >= 1 && data->cmd[i].pipe_fd[0] != -1) // si c'est pas le premier pipe et que pipe_fd[0] est pas fail
//     {
// 		DEBUG();
//         if (dup2(data->cmd[i].pipe_fd[0], STDIN_FILENO) == -1)
//         {
//             perror("2Rachele: dup2");
//             return (0);
//         }
//     }
//     else if (data->cmd[i].pipe_fd[0] != -1)
//     {
//         if (close(data->cmd[i].pipe_fd[0] == -1))
//         {
//             perror("3Rachele: close");
//             return (0);
//         }
//     }
//     if (i <= data->size_cmd_array - 1 && data->cmd[i].pipe_fd[1] != -1) // si c'est pas le dernier pipe et que pipe_fd[0] est pas fail
//     {
//         if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
//         {
//             perror("4Rachele: dup2");
//             return (0);
//         }
//     }
//     else if (data->cmd[i].pipe_fd[0] != -1)
//     {
//         if (close(data->cmd[i].pipe_fd[0]) == -1)
//         {
//             perror("5Rachele: close");
//             return (0);    
//         }
//     }
//     return (1);
// }

// int ft_close_child_fd(t_data *data, int i)
// {
//     int counter;

//     counter = 0;
//     while(counter < data->size_cmd_array)
//     {
//         if (counter != i && counter != i + 1)
//         {
// 			if (!ft_close_pipe(data, counter))
// 				return (0);
//             // if (close(data->cmd[counter].pipe_fd[0]) == -1 || close(data->cmd[counter].pipe_fd[1]) == -1)
//             // {
//             //     perror("5bis Rachele: close:");
//             //     return (0);
//             // }
//         }
//         counter++;
//     }
// }

// int ft_close_pipe(t_data *data, int i)
// {
// 	if (data->cmd[i].pipe_fd[0] != -1)
// 	{
// 		if (close(data->cmd[i].pipe_fd[0]) == -1)
// 		{
// 			perror("6Rachele: close");
// 			return (0);
// 		}
// 	}
// 	if (data->cmd[i].pipe_fd[1] != -1)
// 	{
// 		if (close(data->cmd[i].pipe_fd[1]) == -1)
// 		{
// 			perror("7Rachele: close");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// OLDDDDDDDDDD


// int	create_pipe(t_data *data, int i, bool crea_pipe)
// {
// 	int pipe_fd[2];

// 	if (crea_pipe == true)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 			return (0);
// 		if (data->cmd[i].fd_out == -1)
// 			data->cmd[i].fd_out = pipe_fd[1];
// 		else
// 		{
// 			if (close(pipe_fd[1] == -1))
// 			{
// 				perror("Rachele: close:");
// 				return (0);
// 			}
// 		}
// 		if (data->cmd[i + 1].fd_in == -1)
// 			data->cmd[i + 1].fd_in = pipe_fd[0];
// 		else
// 		{
// 			if (close(pipe_fd[0] == -1))
// 			{
// 				perror("Rachele: close:");
// 				return (0);
// 			}
// 		}
// 	}
// 	// DEBUG("	commande : %s	fd in : %d			fd out : %d", data->cmd[i].the_cmd, data->cmd[i].fd_in, data->cmd[i].fd_out)
// 	return (1);
// }

// int	ft_connect_pipe(t_data *data, int i)
// {
// 	//DEBUG("\n\n\ncommande : %s	fd in : %d			fd out : %d", data->cmd[i].the_cmd, data->cmd[i].fd_in, data->cmd[i].fd_out)
// 	if (data->cmd[i].fd_in != -1)
// 	{
// 		if (dup2(data->cmd[i].fd_in, STDIN_FILENO) == -1)
// 		{
// 			perror("Rachele: dup2:");
// 			return (0);
// 		}
// 		if (close(data->cmd[i].fd_in) == -1)
// 		{
// 			DEBUG("je vais close data->cmd[%d].fd_in", i)
// 			perror("Rachele: close:");
// 			return (0);
// 		}
// 	}
// 	if (data->cmd[i].fd_out != -1)
// 	{
// 		if (dup2(data->cmd[i].fd_out, STDOUT_FILENO) == -1)
// 		{
// 			perror("Rachele: dup2:");
// 			return (0);
// 		}
// 		if (close(data->cmd[i].fd_out) == -1)
// 		{
// 			DEBUG("je vais close data->cmd[%d].fd_out", i)
// 			perror("Rachele: close:");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// int	ft_close_pipe(t_data *data, int i, bool crea_pipe)
// {
// 	if (crea_pipe == true)
// 	{
// 		DEBUG("dans close_pipe chill")
// 		if (data->cmd[i].fd_in != STDIN_FILENO && data->cmd[i].fd_in != -1)
// 		{
// 			DEBUG("je vais close data->cmd[%d].fd_in", i)
// 			if (close(data->cmd[i].fd_in) == -1)
// 			{
// 				perror("Rachele: close:");
// 				return (0);
// 			}
// 		}
// 		if (data->cmd[i].fd_out != STDOUT_FILENO && data->cmd[i].fd_out != -1)
// 		{
// 			DEBUG("je vais close data->cmd[%d].fd_out", i)
// 			if (close(data->cmd[i].fd_out == -1))
// 			{
// 				perror("Rachele: close:");
// 					return (0);
// 			}
// 		}
// 	}
// 	return (1);
// }

// int	ft_close_child_fd(t_data *data, int i, bool crea_pipe)
// {
// 	int j;

// 	if (crea_pipe == true)
// 	{
// 		j = 0;
// 		while (j < data->size_cmd_array)
// 		{
// 			if (i != j)
// 			{
// 				if (!ft_close_pipe(data, j, crea_pipe))
// 					return (0);
// 			}
// 			j++;
// 		}
// 	}
// 	return (1);
// }

// // int	pipe_handler(t_data *data, int i)
// // {
// // 	DEBUG()
// // 	if (data->size_cmd_array <= 1)
// // 		return (1);
// // 	else if (i == 0)
// // 		return (first_pipe_handler(data, i));
// // 	else if (i + 1 == data->size_cmd_array)
// // 		return (last_pipe_handler(data, i));
// // 	else
// // 		return (middle_pipe_handler(data, i));
// // }

// // int first_pipe_handler(t_data *data, int i)
// // {
// // 	if (pipe(data->cmd[i].pipe_fd) == -1)
// // 	{
// // 		perror("Rachele: pipe:");
// // 		return (0);
// // 	}
// // 	if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
// // 	{
// // 		perror("Rachele: dup2:");
// // 		return (0);
// // 	}
// // 	if (close(data->cmd[i].pipe_fd[0]) == -1)
// // 	{
// // 		perror("Rachele: close:");
// // 		return (0);
// // 	}
// // }

// // int last_pipe_handler(t_data *data, int i)
// // {
// // 	if (pipe(data->cmd[i].pipe_fd) == -1)
// // 	{
// // 		perror("Rachele: pipe:");
// // 		return (0);
// // 	}
// // 	if (close(data->cmd[i].pipe_fd[1]) == -1)
// // 	{
// // 		perror("Rachele: close:");
// // 		return (0);
// // 	}
// // 	data->cmd[i].pipe_fd[0] = data->cmd[i - 1]pipe_fd[1];
// // }

// // int	middle_pipe_handler(t_data *data, int i)
// // {
// // 	data->cmd[i].pipe_fd[1] = data->cmd[i + 1]pipe_fd[0];
// // 	data->cmd[i].pipe_fd[0] = data->cmd[i - 1]pipe_fd[1];
// // }

// // int	first_pipe_handler(t_data *data, int i)
// // {
// // 	if (pipe(data->cmd[i].pipe_fd) == -1)
// // 	{
// // 		perror("pipe");
// // 		return (0);
// // 	}
// // 	DEBUG("BEFORE DUP2")
// // 	if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
// // 	{
// // 		DEBUG("AFTER DUP2")
// // 		perror("dup2");
// // 		return (0);
// // 	}
// // 	DEBUG("AFTER DUP2")
// // 	ft_memcpy(data->cmd[i + 1].pipe_fd, data->cmd[i].pipe_fd,
// // 		sizeof(data->cmd[i].pipe_fd));
// // 	return (1);
// // }

// // int	last_pipe_handler(t_data *data, int i)
// // {
// // 	DEBUG()
// // 	if (dup2(data->cmd[i].pipe_fd[0], STDIN_FILENO) == -1)
// // 	{
// // 		perror("dup2");
// // 		return (0);
// // 	}
// // 	return (1);
// // }

// // int	middle_pipe_handler(t_data *data, int i)
// // {
// // 	DEBUG()
// // 	if (dup2(data->cmd[i].pipe_fd[0], STDIN_FILENO) == -1)
// // 	{
// // 		perror("dup2");
// // 		return (0);
// // 	}
// // 	data->cmd[i].multiple_pipe = data->cmd[i].pipe_fd[0];
// // 	if (pipe(data->cmd[i].pipe_fd) == -1)
// // 	{
// // 		perror("pipe");
// // 		return (0);
// // 	}
// // 	if (dup2(data->cmd[i].pipe_fd[1], STDOUT_FILENO) == -1)
// // 	{
// // 		perror("dup2");
// // 		return (0);
// // 	}
// // 	ft_memcpy(data->cmd[i + 1].pipe_fd, data->cmd[i].pipe_fd,
// // 		sizeof(data->cmd[i].pipe_fd));
// // 	return (1);
// // }
