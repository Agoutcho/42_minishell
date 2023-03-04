# Colors
RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
CYAN    = \033[36m

NAME		:=	minishell

CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror 
LFLAGS		:=	libft/libft.a -lreadline

OBJ_FOLDER	:=	objs
SRC_FOLDER	:=	srcs

HEADERFILE	:=	includes/minishell.h
SRCS		:=	builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export_utils.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c \
				execution/builtins_utils.c \
				execution/builtins.c \
				execution/commands.c \
				execution/env_create_node.c \
				execution/env_utils.c \
				execution/exec.c \
				execution/executable.c \
				execution/free.c \
				execution/pipe.c \
				execution/redirections_utils.c \
				execution/redirections.c \
				parsing/add_to_env.c \
				parsing/fill_heredoc.c \
				parsing/free_arg.c \
				parsing/free_fonction.c \
				parsing/init_command.c \
				parsing/init_env_creation.c \
				parsing/init_env.c \
				parsing/init_redir.c \
				parsing/init_term.c \
				parsing/minishell.c \
				parsing/parse_error_pipe.c \
				parsing/parse_error_quote.c \
				parsing/parse_error_redir.c \
				parsing/parse_error.c \
				parsing/parsing_add_command.c \
				parsing/parsing_add_dollar.c \
				parsing/parsing_add_tilde.c \
				parsing/parsing_add_tilde_utils.c \
				parsing/parsing_arg_size.c \
				parsing/parsing_command.c \
				parsing/parsing_count_dollar.c \
				parsing/parsing_input.c \
				parsing/parsing.c \
				parsing/parsing_redirection.c \
				parsing/parsing_tilde_size.c \
				parsing/signal_handler.c \
				parsing/transform_args.c 

OBJS		:=	$(SRCS:%.c=$(OBJ_FOLDER)/%.o)

.SILENT:

all: libs $(NAME)

libs:
	@$(MAKE) -C ./libft/

$(NAME): $(OBJS) libft/libft.a
	@printf "$(YELLOW)[Linking]$(RESET) %s\n" $@
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADERFILE)
	@mkdir -p $(@D)
	@printf "$(CYAN)[Compiling]$(RESET) %s\n" $<
	$(CC) $(CFLAGS) -I/usr/local/opt/readline/include/ -o $@ -c $<

clean:
	$(MAKE) clean -C ./libft/
	@printf "$(GREEN)[Cleaning]$(RESET) object files\n"
	rm -fr $(OBJ_FOLDER)

fclean: clean
	$(MAKE) fclean -C ./libft/
	@printf "$(GREEN)[Cleaning]$(RESET) $(NAME)\n"
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re