# Colors
RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
CYAN    = \033[36m

# Directories
SRCDIRS := srcs/builtins srcs/execution srcs/parsing
OBJDIR  := objs

# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror
LFLAGS  := libft/libft.a -lreadline

# List of object files to build
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c)))

# Targets
EXECUTABLE := Rachele

.PHONY: all clean fclean re

all: $(OBJDIR) $(EXECUTABLE)

$(OBJDIR)/%.o: %.c
	@printf "$(CYAN)[Compiling]$(RESET) %s\n" $<
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(addprefix $(OBJDIR)/, $(SRCDIRS))

$(EXECUTABLE): $(OBJS)
	@printf "$(YELLOW)[Linking]$(RESET) %s\n" $@
	@$(CC) $(OBJS) $(LFLAGS) -o $@

clean:
	@printf "$(GREEN)[Cleaning]$(RESET) object files\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(GREEN)[Cleaning]$(RESET) $(EXECUTABLE)\n"
	@rm -f $(EXECUTABLE)

re: fclean all
