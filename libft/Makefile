#	COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
RED         = \033[1;31m
BLUE        = \033[1;34m

#	NAME
NAME=libft.a

#	PATH
SRC_PATH = ./src/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

#	SRC
SRC_NAME =	ft_atoi.c 				\
			ft_bzero.c 				\
			ft_calloc.c 			\
			ft_isalnum.c 			\
			ft_isalpha.c 			\
			ft_isascii.c 			\
			ft_isdigit.c 			\
			ft_isprint.c 			\
			ft_itoa.c 				\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_memcpy.c 			\
			ft_memmove.c 			\
			ft_memset.c 			\
			ft_putchar_fd.c 		\
			ft_putendl_fd.c 		\
			ft_putnbr_fd.c 			\
			ft_putstr_fd.c 			\
			ft_split.c 				\
			ft_strchr.c 			\
			ft_strcjoin.c			\
			ft_strcmp.c				\
			ft_strdup.c 			\
			ft_strichr.c			\
			ft_striteri.c 			\
			ft_strjoin.c 			\
			ft_strlcat.c 			\
			ft_strlcpy.c 			\
			ft_strlen.c 			\
			ft_strmapi.c 			\
			ft_strncmp.c 			\
			ft_strndup.c			\
			ft_strnstr.c 			\
			ft_strrchr.c			\
			ft_strtrim.c 			\
			ft_substr.c 			\
			ft_tolower.c 			\
			ft_toupper.c 			

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = $(INC_PATH)libft.h

#	FILES
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

#	FLAGS
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_NAME)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $< -o $@
	@echo "$(BLUE)[>LIBFT]	$@ created.$(NOC)"

$(NAME): $(OBJ)
	@ar crs $(NAME) $(OBJ)
	@echo "$(BLUE)[>LIBFT]	$@ created.$(NOC)"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(BLUE)[>LIBFT]	.o files deleted.$(NOC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)[>LIBFT]	$(NAME) deleted.$(NOC)"

ffclean:
	@rm -f $(NAME)
	@echo "$(BLUE)[>LIBFT]	$(NAME) deleted.$(NOC)"

re: fclean all