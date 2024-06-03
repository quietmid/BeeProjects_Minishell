# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 15:36:20 by jlu               #+#    #+#              #
#    Updated: 2024/06/03 13:53:16 by jlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = minishell
NAME = minishell

LIBFT = ./libft/libft.a	

SRC = ./src/main.c \
	  ./src/shell_util.c \
	  ./src/init.c \
	  .src/builtin.c \
	  .src/utils.c \

#BSRC =

CC = cc
CFLAGS = -Wall -Wextra -Werror

RL_HEADER = ~/.brew/Cellar/readline/8.2.10/include
RL_LIB = ~/.brew/Cellar/readline/8.2.10/lib
# needs include
#RLFLAG = -lreadline

# -g
# -fsanitize=address

#Color ANSI Code
BOLD   := \033[1m./SRC/
RED    := \033[31;1m
GREEN  := \033[32;1m
YELLOW := \033[33;1m
BLUE   := \033[34;1m
MAGENTA   := \033[35;1m
CYAN      := \033[36;1m
WHITE     := \033[37;1m
RESET     := \x1b[0m #reseting the text formatting to default state

OBJECTS_DIR = obj
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(SRC:.c=.o)))
BOBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(BSRC:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
		@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -lhistory -L $(RL_LIB) -I$(RL_HEADER) -o $(NAME)
		@echo "$(CYAN)--------------------------------"
		@echo "$(NAME) = Who threw the blue shell!"
		@echo "$(CYAN)--------------------------------$(RESET)"

$(LIBFT):
		@$(MAKE) -C ./libft

$(OBJECTS_DIR)/%.o: ./SRC/%.c
		@mkdir -p $(OBJECTS_DIR)
		@echo "Compiled $(GREEN) $^ $(RESET)"
		@$(CC) $(CFLAGS) -c -o $@ $^

#bonus: $(BSRC) .bonus

#.bonus: $(LIBFT) $(BOBJECTS)
#		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
#		@touch .bonus
#		@$(CC) $(CFLAGS) $(BOBJECTS) $(LIBFT) -o $(NAME)
#		@echo "$(CYAN)--------------------------------"
#		@echo "$(NAME) = you have activated my bonus 😏!"
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