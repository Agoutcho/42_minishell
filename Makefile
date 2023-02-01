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
			init_command.c \
			init_env.c \
			init_term.c	\
			parsing.c \
			parse_error.c \
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
CC = gcc $(CFLAGS)
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