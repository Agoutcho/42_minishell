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

typedef struct s_command {
    char    **env;
    // gérer les redirections j'ai pas encore d'idée de comment faire. 
    char    **parsed_line;
    char    *input;
    char    *exec_path;      //le path de la commande a executer
    int        outfile;      // les files descriptor
    int        infile;
    int        heredoc;
    bool    is_builtins;
    bool    error;
}    t_command;

// @INIT_TERM_C
void	set_term(struct termios *term, bool mode);
void	init_term(bool mode);
// @INIT_ENV_C

// @SIG_HANDLER_C
void	sig_handler(int sig);

#endif