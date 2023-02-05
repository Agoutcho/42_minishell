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
# define DEBUG(x, ...) printf("[%s:%d] "x"\n",__FUNCTION__ ,__LINE__, ##__VA_ARGS__);

// valgrind --leak-check=full --show-leak-kinds=all 2> text.txt ./minishell

typedef enum e_quote {
    e_no_quote,
    e_big_quote,        // ""
    e_little_quote,     // ''
}   t_quote;

typedef struct s_env {
    char *key; // PATH= //malloc
    char *value; // /bin/:/usr/bin //malloc
    int affiche_env; // 0 ou 1
    struct s_env *first;
    struct s_env *next;
}    t_env;

typedef struct s_path {
    char *path; // PATH=/bin/:/usr/bin
    char **path_splitted; // [0] = "/bin/" [1] = "/usr/bin"
}    t_path;

// /**
//  * @brief Structure pour les redirections
//  *        size est le nombre de redirection
//  *        redir est un tableau avec toutes les redirections
//  */
// typedef struct s_redirect_array {
//     unsigned long size;
//     t_redirect *redir_array;
// }   t_redirect_array;

typedef enum e_redir {
    e_in = 1, // ( < )
    e_out,    // ( > )
    e_append, // ( >> )
    e_heredoc // ( << )
}   t_redir;

/**
 * @brief Structure pour les redirections
 *        type le type de redirection
 *        file_name le nom du fichier 
 */
typedef struct s_redirect {
    t_redir type;
    char *file_name;
}   t_redirect;

/**
 * @brief Structure avec la commande, 
 *        les arguments et options de la commande
 *        et un boolean qui indique si la commande
 *        a ete trouve ou pas
 */
typedef struct s_cmd_array {
    char *the_cmd;
    char **args;
    int is_cmd_filled;
    unsigned long redir_size;
    t_redirect *redir_array;
}   t_cmd_array;

/**
 * @brief Une structure avec un tableau de commande
 *        de taille size. 
 *        Separer par les pipes
 */
typedef struct s_cmd_hub {
    unsigned long size;
    t_cmd_array *cmd_array; //maloc
}   t_cmd_hub;

typedef struct s_command {
    t_env    *env; //malloc
    t_path   path;
    t_quote  quote;
    t_cmd_hub cmd;
    char    *input;
    char    *exec_path;      //le path de la commande a executer
    int        outfile;      // les files descriptor
    int        infile;
    int        heredoc;
    bool    is_builtins;
    bool    error;
}    t_command;

// PARSING
void parsing(t_command *command);
void check_parse_error(t_command *command);
void init_command(t_command *command);
void init_redir(t_command *command);
int init_env(t_command *command, char **env);
t_env *find_env_value(t_command *command, char *key);
void big_free(t_command *command);
void set_quote(t_command *command, long *i);


// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);

#endif