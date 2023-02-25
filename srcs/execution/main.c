#include "../../includes/minishell.h"
void print_data(t_data data, int n);

// int	g_exit_code;

// int main(int argc, char **argv, char **env)
// {
// 	int num_cmds;
// 	printf("Enter number of commands: ");
// 	scanf("%d", &num_cmds);

// 	t_data data;
// 	data.cmd = (t_cmd_array *)malloc(sizeof(t_cmd_array) * num_cmds + 1);
// 	data.size_cmd_array = num_cmds;
	
// 	for (int i = 0; i < num_cmds; i++)
// 	{
// 		printf("Enter command name: ");
// 		char cmd_name[100];
// 		scanf("%s", cmd_name);
// 		data.cmd[i].the_cmd = strdup(cmd_name);

// 		printf("Enter number of arguments: ");
// 		int num_args;
// 		scanf("%d", &num_args);

// 		data.cmd[i].args = (char **)malloc(sizeof(char *) * (num_args + 1));

// 		for (int j = 0; j < num_args; j++)
// 		{
// 			printf("Enter argument %d: ", j + 1);
// 			char arg[100];
// 			scanf("%s", arg);
// 			data.cmd[i].args[j] = strdup(arg);
// 		}
// 		data.cmd[i].args[num_args] = NULL;

// 		printf("Enter number of redirections: ");
// 		int num_redirs;
// 		scanf("%d", &num_redirs);

// 		data.cmd[i].redir_array = (t_redirect *)malloc(sizeof(t_redirect) * num_redirs);
// 		data.cmd[i].redir_size = num_redirs;

// 		for (int j = 0; j < num_redirs; j++)
// 		{
// 			printf("Enter redirection type: ");
// 			int type;
// 			scanf("%d", &type);
// 			data.cmd[i].redir_array[j].type = type;

// 			if (type == 4)
// 			{
// 				printf("Enter number of lines for heredoc: ");
// 				int n;
// 				scanf("%d", &n);

// 				t_heredoc *first = NULL;
// 				t_heredoc *prev = NULL;
// 				for (int k = 0; k < n; k++)
// 				{
// 					printf("Enter line %d: ", k + 1);
// 					char line[100];
// 					scanf("%s", line);

// 					t_heredoc *temp = malloc(sizeof(t_heredoc));
// 					temp->line = strdup(line);
// 					temp->next = NULL;
// 					if (!first)
// 						first = temp;
// 					if (prev)
// 						prev->next = temp;
// 					prev = temp;
// 				}
// 				data.cmd[i].redir_array[j].heredoc = first;
// 				data.cmd[i].redir_array[j].file_name = ft_strdup("/tmp/heredoc_file");
// 			}
// 			else
// 			{
// 				printf("Enter file name: ");
// 				char file_name[100];
// 				scanf("%s", file_name);
// 				data.cmd[i].redir_array[j].file_name = strdup(file_name);
// 			}
// 			data.cmd[i].redir_array[j].file_fd = -1;
// 		}
// 	}
// 	data.fd_saver.stdin = dup(0);
// 	data.fd_saver.stdout = dup(1);
// 	data.fd_saver.stderr = dup(2);
// 	init_env(&data, env);
// 	if (!execution(&data));
// 	free_data(&data);
// 	close(data.fd_saver.stdin);
// 	close(data.fd_saver.stdout);
// 	close(data.fd_saver.stderr);
// 	// while (1)
// 	// 	;
// 	//print_data(data, num_cmds);
// 	free_data(&data);
// 	return (0);
// }

// void print_data(t_data data, int n)
// {
// 	for (int i = 0; i < n; i++)
// 	{
// 		printf("\n");
// 		printf("CMD: %s\n", data.cmd[i].the_cmd);
// 		printf("ARGS:\n");
// 		for (int j = 0; data.cmd[i].args[j]; j++)
// 			printf("\t%s\n", data.cmd[i].args[j]);
// 		printf("REDIR_SIZE: %ld\n", data.cmd[i].redir_size);
// 		printf("REDIR_ARRAY:\n");
// 		for (int j = 0; j < data.cmd[i].redir_size; j++)
// 		{
// 			printf("\tTYPE: %d\n", data.cmd[i].redir_array[j].type);
// 			printf("\tFILE_NAME: %s\n", data.cmd[i].redir_array[j].file_name);
// 			printf("\tFILE_FD: %d\n", data.cmd[i].redir_array[j].file_fd);
// 		}
// 	}
// }