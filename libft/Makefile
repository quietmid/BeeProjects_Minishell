# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 16:27:29 by jlu               #+#    #+#              #
#    Updated: 2024/05/31 15:46:55 by jlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = libft
NAME = libft.a

LIBH = libft.h

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strchr.c \
	  ft_strlcat.c \
	  ft_strcpy.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strncmp.c \
	  ft_strcmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  
BSRC = ft_lstnew_bonus.c \
	   ft_lstadd_front_bonus.c \
	   ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c \
	   ft_lstadd_back_bonus.c \
	   ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c \
	   ft_lstiter_bonus.c \
	   ft_lstmap_bonus.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

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

$(NAME): $(OBJECTS) $(BOBJECTS)
		@ar rcs $(NAME) $(OBJECTS) $(BOBJECTS)
		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
		@echo "$(CYAN)--------------------------------"
		@echo "$(NAME) = LIBFT at your service"
		@echo "$(CYAN)--------------------------------$(RESET)"

$(OBJECTS_DIR)/%.o: ./%.c 
		@mkdir -p $(OBJECTS_DIR)
		@$(CC) $(CFLAGS) -c -o $@ $^ 
		
clean: 
		@rm -rf $(OBJECTS_DIR)/*.o
		@rm -rf .bonus
		@rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@echo "$(WHITE) $(PROJECT) $(RESET) $(GREEN) LIBFT SERVICE COMPLETED"
	
re: fclean all 

.PHONY: all clean fclean re bonus
