#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

// typedef struct s_command {
//     int        argc;        // nombre de mots dans argv
//     char    **argv;         //ce que j'ai recup dans le prompt
//     // gérer les redirections j'ai pas encore d'idée de comment faire. 
//     char    *exec_path;      //le path de la commande a executer
//     int        outfile;      // les files descriptor
//     int        infile;
//     int        heredoc;
//     bool    is_builtins;
//     bool    error;
// }    t_command;

void parsing(int argc, char **argv, char **env);

#endif