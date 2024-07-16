
PROJECT = minishell

NAME = minishell

LIBFT = ./libft/libft.a	

SRC =	./src/builtin.c \
		./src/builtin_cd.c \
		./src/builtin_echo.c \
		./src/builtin_env.c \
		./src/builtin_export.c \
		./src/builtin_init.c \
		./src/envp_init.c \
		./src/errors.c \
		./src/exec_child.c \
		./src/exec_redir_builtin.c \
		./src/exec_redirect.c \
 		./src/exec_redirect_fd.c \
		./src/expand.c \
		./src/expand_helpers.c \
		./src/free_all.c \
		./src/here_doc.c \
		./src/main.c \
		./src/parse.c \
		./src/parse_util.c \
		./src/parse_util2.c \
		./src/pipes.c \
		./src/prompt_check.c \
		./src/safe_malloc.c \
		./src/signal.c \
		./src/unquotes.c \
		./src/utils.c \
		./src/utils_helpers.c \
		./src/utils_helpers2.c \
		./src/safe_func.c \

#BSRC =

CC = cc
CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror

# -g -fsanitize=address

RL_HEADER = ~/.brew/Cellar/readline/8.2.10/include
RL_LIB = ~/.brew/Cellar/readline/8.2.10/lib

OBJECTS_DIR = ./obj

OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(SRC:.c=.o)))
# BOBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(BSRC:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "Compiled with $(BLUE)$(CFLAGS) $(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -lhistory -L $(RL_LIB) -I$(RL_HEADER) -o $(NAME)
	@echo "$(CYAN)--------------------------------"
	@echo "$(NAME) = Who threw the red shell!"
	@echo "$(CYAN)-------------------------------- $(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJECTS_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJECTS_DIR)
	@echo "Compiled $(GREEN) $^ $(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

#bonus: $(BSRC) .bonus

#.bonus: $(LIBFT) $(BOBJECTS)
#		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
#		@touch .bonus
#		@$(CC) $(CFLAGS) $(BOBJECTS) $(LIBFT) -o $(NAME)
#		@echo "$(CYAN)--------------------------------"
#		@echo "$(NAME) = God damn blue shell!"
#		@echo "$(CYAN)--------------------------------$(RESET)"
#		@rm -f $(OBJECTS)

#$(OBJECTS_DIR)/%.o: ./BSRC/%.c
#		@mkdir -p $(OBJECTS_DIR)
#		@echo "Compiled $(GREEN) $^ $(RESET)"
#		@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJECTS_DIR)/*.o
	@rm -rf .bonus
	@rm -rf .here_doc_temp
	@rm -rf obj

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "$(WHITE) $(PROJECT) $(RESET) $(GREEN) FULLY CLEANED"

re: fclean all

.PHONY: all clean fclean re bonus

#Color ANSI Code
BOLD   := \033[1m
RED    := \033[31;1m
GREEN  := \033[32;1m
YELLOW := \033[33;1m
BLUE   := \033[34;1m
MAGENTA   := \033[35;1m
CYAN      := \033[36;1m
WHITE     := \033[37;1m
RESET     := \033[0m  #reseting the text formatting to default state