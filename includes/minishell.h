/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:59:51 by nradal            #+#    #+#             */
/*   Updated: 2023/02/17 17:06:43 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

extern int	g_exit_code;

typedef enum e_redir {
	e_in = 1,
	e_out,
	e_append,
	e_heredoc
}	t_redir;

typedef struct s_fd_saver {
	int	stdin;
	int	stdout;
	int	stderr;
}	t_fd_saver;

typedef struct s_heredoc {
	char				*line;
	struct s_heredoc	*first;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_redirect {
	t_redir		type;
	t_heredoc	*heredoc;
	char		*file_name;
	int			file_fd;
}	t_redirect;

typedef struct s_cmd_array {
	char			*the_cmd;
	char			**args;
	int				pipe_fd[2];
	int				multiple_pipe;
	int				redir_size;
	t_redirect		*redir_array;
}	t_cmd_array;

typedef struct s_env {
	char			*key;
	char			*value;
	int				affiche_env;
	struct s_env	*first;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	t_cmd_array		*cmd;
	t_env			*env;
	t_fd_saver		fd_saver;
	unsigned long	size_cmd_array;
}	t_data;

// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);

// @EXEC
int		execution(t_data *data);
bool	is_executable(char *path);
int		executable_handler(t_cmd_array *cmd, t_env *env);

//@BUILTINS/
//	@BUILTINS_UTILS/
//			@EXPORT_UTILS_C
int		get_key_length(char *arg);
char	*get_key(char *arg);
char	*get_value(char *arg);
int		ft_export_no_args(t_env *env);
char	**sort_strs(char **strs);
//	@CD_C
int		ft_cd(t_cmd_array *cmd, t_env *env);
int		change_pwd(t_env *env, char *pwd_oldpwd_flag);
int		cd_oldpwd(t_cmd_array *cmd, t_env *env);
//	@ECHO_C
int		ft_echo(char **args);
//	@ENV_C
int		ft_env(t_env *env);
//	@EXIT_C
int		ft_exit(char **args);
int		get_exit_code(char *arg);
int		overflow_atoi(const char *str);
int		is_exit_arg_valid(char *arg);
void	exit_shell(void);
//	@EXPORT_C
int		handle_export_arg(char *arg, t_env **env);
int		ft_export(t_cmd_array *cmd, t_env *env);
int		is_valid_arg(char *arg);
int		split_arg_on_equal_sign(char *arg, char **key, char **value);
//	@PWD_C
int		ft_pwd(char **args);
//	@UNSET_C
int		ft_unset(t_cmd_array *cmd, t_env *env);
int		unset_keys(t_cmd_array *cmd, t_env *env);
int		get_unset_key(char *arg, char **key);
//@EXEC_C
int		execution(t_data *data);
int		execute(t_data *data, int i);
//@BUILTINS_C
int		builtins_handler(t_data *data, int i);
char	**init_builtins_tab(char **builtins);
int		is_builtins(char *cmd);
//@BUILTINS_UTILS_C
void	error_builtins_handler(t_cmd_array *cmd);
bool	option_checker(char **args);
bool	builtin_option_checker(int cmd_id, char **args);
//@EXECUTABLE_C
void	error_executable_handler(char *path, int error);
bool	is_executable(char *path);
int		executable_handler(t_cmd_array *cmd, t_env *env);
//@ENV_UTILS_C
void	remove_node(t_env *env);
t_env	*search_key(char *key, t_env *env);
int		replace_node(t_env *env, char *value);
char	**env_to_array(t_env *env_list);
//@ENV_CREATE_NODE_C
int		create_node(t_env *env, char *key, char *value);
t_env	*init_new_node(void);
int		set_key(t_env *node, char *key);
int		set_value(t_env *node, char *value);
//@FREE_C
void	free_data(t_data *data);
void	free_strs(char **strs);
//@REDIRECTIONS_C
int		redirections_handler(t_cmd_array *cmd);
int		e_in_handler(t_redirect *redir);
int		e_out_handler(t_redirect *redir);
int		e_append_handler(t_redirect *redir);
int		e_heredoc_handler(t_redirect *redir);
//@REDIRECTIONS_UTILS_C
int		redirections_closer(t_cmd_array *cmd, t_fd_saver fd_saver);
//@TEMPORAIRE
int		check_printable(char *str);
int		add_to_env(t_data *data, char *str);
t_env	*find_env_value(t_data *data, char *key);
char	*change_shlvl(char *env_value);
int		lst_add_env_value(char *envp, t_env *env);
int		lst_add_back_env(t_data *data, char **env, int j);
int		copy_env(t_data *data, char **env);
void	print_list(t_env *env);
int		init_env(t_data *data, char **env);
//@PIPE_C
int		pipe_handler(t_data *data, int i);
int		first_pipe_handler(t_data *data, int i);
int		last_pipe_handler(t_data *data, int i);
int		middle_pipe_handler(t_data *data, int i);
//@PIPE_CLOSER_C
int		pipe_closer(t_data *data, int i);
int		close_first_pipe(t_data *data, int i);
int		close_last_pipe(t_data *data, int i);
int		close_middle_pipe(t_data *data, int i);
//@COMMANDS_C
char	*get_path(char *cmd, char **env);
int		commands_handler(t_cmd_array *cmd, t_env *env);
char	**add_element_to_array(char **array, char *element);

#endif