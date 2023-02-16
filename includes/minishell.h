#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
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
/* valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full 
--show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes 
--read-var-info=yes */
extern char **environ;
int g_exit_code;

typedef enum e_quote 
{
    e_no_quote,
    e_big_quote = 34,        // ""
    e_little_quote = 39,     // ''
}   t_quote;

typedef struct s_env 
{
    char *key; // PATH= //malloc
    char *value; // /bin/:/usr/bin //malloc
    int affiche_env; // 0 ou 1
    struct s_env *first;
    struct s_env *next;
}    t_env;

// /**
//  * @brief Structure pour les redirections
//  *        size est le nombre de redirection
//  *        redir est un tableau avec toutes les redirections
//  */
// typedef struct s_redirect_array {
//     unsigned long size;
//     t_redirect *redir_array;
// }   t_redirect_array;

typedef enum e_redir 
{
    e_in = 1, // ( < )
    e_out,    // ( > )
    e_append, // ( >> )
    e_heredoc // ( << )
}   t_redir;

typedef struct s_heredoc
{
    char *line;
    struct s_heredoc *first;
    struct s_heredoc *next;
} t_heredoc;

/**
 * @brief Structure pour les redirections
 *        type le type de redirection
 *        file_name le nom du fichier 
 */
typedef struct s_redirect 
{
    t_redir type;
    char *file_name;
    int file_fd;
}   t_redirect;

/**
 * @brief Structure pour les argumnts
 *        liste chainee de tous les args
 *        arg l'argument apres la commande
 */
typedef struct s_args 
{
    struct s_args *first;
    struct s_args *next;
    char *arg; //malloc
} t_args;

/**
 * @brief Structure avec la commande, 
 *        les arguments et options de la commande
 *        et un boolean qui indique si la commande
 *        a ete trouve ou pas
 */
typedef struct s_cmd_array 
{
    char *the_cmd; //malloc
    t_args *args; // malloc liste chainee
    int is_cmd_filled;
    unsigned long redir_size;
    t_redirect *redir_array;
}   t_cmd_array;

/**
 * @brief cmd_array
 *        Une structure avec un tableau de commande
 *        de taille size. 
 *        Separer par les pipes
 */
typedef struct s_command 
{
    t_env    *env; //malloc
    t_quote  quote;
    t_cmd_array *cmd_array; //malloc
    unsigned long size_cmd_array; // init a 0
    long     i_input;
    char    *input;
    char	*hd_line;
    t_heredoc *heredoc;
}    t_command;

// PARSING
void parsing(t_command *command);
void check_parse_error(t_command *command);
void init_command(t_command *command);
void init_redir(t_command *command);
int init_env(t_command *command, char **env);
t_env *find_env_value(t_command *command, char *key);
void big_free(t_command *command);
void set_quote(t_command *command, long *i, int change_i);
long move_space(char *str, long *i);
char *add_command(t_command *command, char *str, long *i, int size);
void parsing_input(t_command *command);
int is_redir(char c);
int count_arg_size(t_command *command, char *str, long i);
int	fill_heredoc(t_command *command, char *heredoc);
void	tout_free(char *input);


// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);

#endif
