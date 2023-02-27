/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:43:01 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/27 09:12:31 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
#include "../libft/includes/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <dirent.h>
#include <unistd.h>

/**
 * @brief USE as a debug printf 
 *        x is the text to add with % as printf
 * 
 * @param x : has to be a char *
 * @param ... : is variadic macros
 * 
 * DOC : https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html#Variadic-Macros
 */
# define DEBUG(x, ...) printf("[%s][%s:%d] "x"\n",__FILE__, __FUNCTION__ ,__LINE__, ##__VA_ARGS__);

# define BLACK  printf("\033[0;30m");
# define RED    printf("\033[0;31m");
# define GREEN  printf("\033[0;32m");
# define YELLOW printf("\033[0;33m");
# define BLUE   printf("\033[0;34m");
# define PURPLE printf("\033[0;35m");
# define CYAN   printf("\033[0;36m");
# define WHITE  printf("\033[0;37m");
# define RESET  printf("\033[0m");

// valgrind --leak-check=full --show-leak-kinds=all 2> text.txt ./minishell
/* valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes */
extern char **environ;
int	g_exit_code;

typedef enum	e_redir 
{
	e_in = 1, // ( < )
	e_out,    // ( > )
	e_append, // ( >> )
	e_heredoc // ( << )
}				t_redir;

typedef struct	s_fd_saver
{
	int	stdin;
	int	stdout;
	int	stderr;
}				t_fd_saver;

typedef struct	s_heredoc
{
	char				*line;
	struct s_heredoc	*first;
	struct s_heredoc	*next;
}				t_heredoc;

/**
 * @brief Structure pour les redirections
 *        type le type de redirection
 *        file_name le nom du fichier 
 */
typedef struct	s_redirect 
{
	t_redir		type;
	char		*hd_line;
	t_heredoc	*heredoc;
	char		*file_name; // malloc
	int			file_fd;
}				t_redirect;

/**
 * @brief Structure pour les argumnts
 *        liste chainee de tous les args
 *        arg l'argument apres la commande
 */
typedef struct	s_args 
{
	struct s_args	*first;
	struct s_args	*next;
	char			*arg; //malloc
}				t_args;

/**
 * @brief Structure avec la commande, 
 *        les arguments et options de la commande
 *        et un boolean qui indique si la commande
 *        a ete trouve ou pas
 */
typedef struct	s_cmd_array 
{
	char		*the_cmd; //malloc
	char		**args;
	t_args		*arg; // malloc liste chainee
	int			is_cmd_filled;
	int			pipe_fd[2];
	int			multiple_pipe;
	long		redir_size;
	t_redirect	*redir_array; //malloc 
}				t_cmd_array;


typedef enum	e_quote 
{
	e_no_quote,
	e_big_quote = 34,        // ""
	e_little_quote = 39,     // ''
}				t_quote;

typedef struct	s_env 
{
	char			*key; // PATH= //malloc
	char			*value; // /bin/:/usr/bin //malloc
	int				affiche_env; // 0 ou 1
	struct s_env	*first;
	struct s_env	*next;
}				t_env;

/**
 * @brief cmd
 *        Une structure avec un tableau de commande
 *        de taille size. 
 *        Separer par les pipes
 */
typedef struct	s_data 
{
	t_env		*env; // malloc liste chainee
	t_quote		quote;
	t_cmd_array	*cmd; //malloc
	long		size_cmd_array; // init a 0
	t_fd_saver	fd_saver;
	long		i_input;
	char		*input;
}				t_data;

// PARSE ERROR SYNTAX ERROR
int		check_parse_error(t_data *data);
int		check_redir(t_data *data);
int		check_pipe(t_data *data);
int		check_quotes(t_data *data);
int		exit_error(char c, char *input, t_data *data);

// INIT ENV
int		init_env(t_data *data, char **env);
int		lst_add_back_env(t_data *data, char **env, int j);
int 	lst_add_env_value(char *envp, t_env *env);

// INIT REDIR
void	init_redir(t_data *data);
int		is_redir(char c);

//INIT COMMAND
void	init_command(t_data *data);
void	set_quote(t_data *data, long *i, int change_i);

// PARSING
int		parsing(t_data *data);
void	parsing_input(t_data *data);
void	do_redirection(t_data *data, long ic, long *i, long *k);
void	do_command(t_data *data, long i_cmd, long *i);
int		count_arg_size(t_data *data, char *str, long i);
int		count_dollar_size(t_data *data, char *str, long *i, int *counter);
int		count_tilde_size(t_data *data, char *str, long *i);
int		is_tilde_ok(char *str, long i);
void	add_dollar(t_data *data, long *i, char *temp, long *index);
void	add_tilde(t_data *data, long *i, char *temp, long *i_temp);
int		add_tilde_home(t_data *data, long *i, char *parsed, long *index);
int		add_tilde_plus(t_data *data, long *i, char *parsed, long *index);
int 	add_tilde_hyphen(t_data *data, long *i, char *parsed, long *index);
int		is_stop_char(t_data *data, char c);
int		is_dollar_ok(char *str, long *i, int change_i);
char	*add_command(t_data *data, char *str, long *i, int size);
void	find_val_in_env(t_data *data, char *t_key, char *parsed, long *idex);
int		find_lenght_in_env(t_data *data, char *str);
t_env	*find_env_value(t_data *data, char *key);
void	big_free(t_data *data);
long	move_space(char *str, long *i);
int		fill_heredoc(t_redirect *data, char *heredoc);
int		add_to_env(t_data *data, char *str);
void	transform_args(t_data *data);

// Free fonctions
void	free_env(t_data *data);
void	free_cmd(t_data *data);
void	free_heredoc(t_redirect *data);
void	secure_char_free(char *input);
void	free_args_char(t_data *data, long i);
void	free_arg_lst(t_data *data, long i);

// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);
void	sig_handler_heredoc(int sig);
void	sig_quit_handler_heredoc(int signum);
void	sig_action(void);

int	set_g_exit_code(int code, int return_value);

///////////////////////////////////////////////////////////////////////////////


// @EXEC
int		execution(t_data *data);
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
int		cd_home(t_env *env);
int		cd_oldpwd(t_env *env);
int		is_directory(char *path);
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
int		ft_pwd(void);
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
void	error_builtins_handler(t_cmd_array *cmd, char *arg);
bool	option_checker(char **args);
bool	builtin_option_checker(int cmd_id, char **args);
//@EXECUTABLE_C
void	error_executable_handler(char *path, int error);
int		is_executable(char *path);
int		executable_handler(t_cmd_array *cmd, t_env *env);
//@ENV_UTILS_C
void	remove_node(t_env *env);
t_env	*search_key(char *key, t_env *env);
int		replace_node(t_env *env, char *value);
char	**env_to_array(t_env *env_list);
char	**env_to_array_plus_quotes(t_env *env_list);
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
// int		check_printable(char *str);
int		add_to_env(t_data *data, char *str);
t_env	*find_env_value(t_data *data, char *key);
// char	*change_shlvl(char *env_value);
int		lst_add_env_value(char *envp, t_env *env);
int		lst_add_back_env(t_data *data, char **env, int j);
// int		copy_env(t_data *data, char **env);
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
