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

typedef enum s_redir {
    in = 1, // ( < )
    out,    // ( > )
    append, // ( >> )
    heredoc // ( << )
}   t_redir;

typedef enum s_quote {
    no_quote,
    big_quote,        // ""
    little_quote,     // ''
}   t_quote;

typedef struct s_parsing {
    char *key; //PATH=
    char *value; // /bin/:/usr/bin
    int affiche_env; // 0 ou 1
    struct s_env *next;
    t_quote quote;
}    t_parsing;

typedef struct s_env {
    char *key; // PATH=
    char *value; // /bin/:/usr/bin
    int affiche_env; // 0 ou 1
    struct s_env *next;
}    t_env;

typedef struct s_path {
    char *path; // PATH=/bin/:/usr/bin
    char **path_splitted; // [0] = "/bin/" [1] = "/usr/bin"
}    t_path;

typedef struct s_command {
    t_env    *env;
    t_path   path;
    t_quote  quote;
    char    **parsed_line;
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

// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);

#endif