# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gufreire <gufreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 19:44:06 by gufreire          #+#    #+#              #
#    Updated: 2025/05/22 20:38:09 by gufreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
CC		= cc
CFLAGS 	=  -Wall -Wextra -Werror -g -Iinc
RM		= rm -f


# Directories
SRC_DIR = src
OBJ_DIR = obj

# Libraries
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a
LIBS		= -lreadline -lncurses -ltermcap

# struct functions directory
STRC_DIR = src/strc
STRC_FILES = structs.c
SRC_STRC = $(addprefix $(STRC_DIR)/, $(STRC_FILES))

# parsing functions directory
PARS_DIR = src/pars
PARS_FILES = token.c
SRC_PARS = $(addprefix $(PARS_DIR)/, $(PARS_FILES))

# todos por agora
TODOS_DIR = src/todos
TODOS_FILES = cd.c check_envp.c check_tokens.c copy_envp.c create_cmd_list.c dolar.c echo.c env.c exe.c execute_builtin.c execute_commands.c export.c external_commands.c finders.c ft_free.c ft_isspace.c ft_strcat.c ft_strcmp.c ft_strcpy.c ft_strdup_two.c ft_strjoin_free.c ft_strndup.c handle_heredoc.c input_analizes.c main.c pipeline.c print_lst.c prompt.c pwd.c quote_checker.c quote_handle.c redirection.c set_envvar.c set_envvar2.c signal.c tokenization.c type_tokens.c unset.c utils.c
SRC_TODOS = $(addprefix $(TODOS_DIR)/, $(TODOS_FILES))

SRC = $(SRC_STRC) $(SRC_PARS) $(SRC_TODOS)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
	

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(STRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TODOS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

valgrind:
	valgrind --suppressions=readline.supp  --track-fds=all --leak-check=full --show-leak-kinds=all ./minishell || true

re: fclean all

.PHONY: all clean fclean re