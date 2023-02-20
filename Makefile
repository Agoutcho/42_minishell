#	COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
RED         = \033[1;31m
BLUE        = \033[1;34m

#	NAME
NAME=minishell

#	PATH
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_DIR = ./includes/

#	SRC
SRC_NAME =	minishell.c	\
			add_to_env.c \
			fill_heredoc.c \
			init_command.c \
			init_env.c \
			init_env_creation.c \
			init_redir.c \
			init_term.c	\
			parse_error.c \
			parse_error_pipe.c \
			parse_error_quote.c \
			parse_error_redir.c \
			parsing.c \
			parsing_input.c \
			parsing_add_command.c \
			parsing_add_dollar.c \
			parsing_add_tilde.c \
			parsing_add_tilde_utils.c \
			parsing_arg_size.c \
			parsing_count_dollar.c \
			parsing_command.c \
			parsing_redirection.c \
			parsing_tilde_size.c \

# signal_handler.c	\
			
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = $(INC_DIR)$(NAME).h

#	FILES
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

#	LIBFT
FT = ./libft/
FT_LIB = $(addprefix $(FT),libft.a)

#	FLAGS
CC = gcc -g3 $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror

all: $(FT_LIB) $(NAME)

$(FT_LIB): FORCE
	@make --no-print-directory -C $(FT)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_NAME) $(FT_LIB)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $< -o $@
	@echo "$(GREEN)[>]		$@ created.$(NOC)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -lreadline $(FT_LIB) -o $@
	@echo "$(GREEN)[>]		$@ created.$(NOC)"

FORCE:

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(GREEN)[>]		.o files deleted.$(NOC)"
	@make --no-print-directory -C $(FT) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)[>]		$(NAME) deleted.$(NOC)"
	@make --no-print-directory -C $(FT) ffclean

re: fclean all