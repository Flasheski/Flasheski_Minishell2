##
## EPITECH PROJECT, 2026
## G-PSU-200-LIL-2-1-minishell-2-1
## File description:
## Makefile
##

# -- Couleurs
END     = \033[0m
BOLD    = \033[1m
CYAN    = \033[36m
GREEN   = \033[32m
PURPLE  = \033[35m
YELLOW  = \033[33m
GREY    = \033[90m

define FLASHESKI_LOGO
 @echo "\n"
 @echo "$(BOLD)$(CYAN)  ___ _      _   ___ _  _ ___ ___ _  _____ $(END)"
 @echo "$(BOLD)$(CYAN) | __| |    /_\ / __| || | __/ __| |/ /_ _|$(END)"
 @echo "$(BOLD)$(CYAN) | _|| |__ / _ \\__  \ __ | _|\__ \ ' < | | $(END)"
 @echo "$(BOLD)$(CYAN) |_| |____/_/ \_\___/_||_|___|___/_|\_\___|$(END)"
 @echo "$(BOLD)$(MAGENTA)          >> $(NAME) compilé ! <<$(END)"
 @echo "\n"
endef

CC      =   epiclang

SRC =   src/commands/find_command.c \
		src/commands/handle_command.c \
		src/commands/cd_command.c \
		src/commands/print_cd_path.c \
		src/envs/put_env.c \
		src/envs/my_setenv.c \
		src/envs/my_unsetenv.c \
		src/envs/free_env.c \
		src/paths/check_paths.c \
		src/paths/get_path.c \
		src/paths/process_lines.c \
		src/pipes/check_pipes.c \
		src/pipes/handle_pipe.c \
		src/redirects/handle_redirections.c \
		src/exec/exec.c \
		src/signals/signals.c \
		src/utils/free_array.c \
		bonus/display_bonus.c \
		src/main.c

OBJ =   $(SRC:.c=.o)

NAME    =   mysh

CPPFLAGS =  -I./include
CFLAGS  =   -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/my
	$(CC) -o $(NAME) $(OBJ) -L./lib/my -lmy
	$(FLASHESKI_LOGO)

clean:
	$(MAKE) -C ./lib/my clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ./lib/my fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re
