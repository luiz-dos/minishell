# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gufreire <gufreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 19:44:06 by gufreire          #+#    #+#              #
#    Updated: 2025/05/28 17:31:54 by gufreire         ###   ########.fr        #
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

<<<<<<< HEAD
# cmd functions directory
CMD_DIR = src/cmd
CMD_FILES = cd.c create_cmd_list.c echo.c export.c external_commands.c pwd.c unset.c
SRC_CMD = $(addprefix $(CMD_DIR)/, $(CMD_FILES))

# env functions directory
ENV_DIR = src/env
ENV_FILES = check_envp.c copy_envp.c env.c prompt.c set_envvar.c set_envvar2.c
SRC_ENV = $(addprefix $(ENV_DIR)/, $(ENV_FILES))

# exc functions directory
EXC_DIR = src/exc
EXC_FILES = exe.c execute_builtin.c execute_commands.c
SRC_EXC = $(addprefix $(EXC_DIR)/, $(EXC_FILES))

# handle functions directory
HDL_DIR = src/hdl
HDL_FILES = dolar.c handle_heredoc.c pipeline.c redirection.c
SRC_HDL = $(addprefix $(HDL_DIR)/, $(HDL_FILES))

# main functions directory
MAIN_DIR = src/main
MAIN_FILES = main.c signal.c
SRC_MAIN = $(addprefix $(MAIN_DIR)/, $(MAIN_FILES))

# parsing functions directory
PARS_DIR = src/pars
PARS_FILES = check_tokens.c input_analizes.c quote_checker.c quote_handle.c strip_quotes.c tokenization.c type_tokens.c
SRC_PARS = $(addprefix $(PARS_DIR)/, $(PARS_FILES))

# struct functions directory
STRC_DIR = src/strc
STRC_FILES = structs.c
SRC_STRC = $(addprefix $(STRC_DIR)/, $(STRC_FILES))

# Utils functions directory
UTILS_DIR = src/utils
UTILS_FILES = finders.c ft_free.c ft_isspace.c ft_strcat.c ft_strcmp.c ft_strcpy.c ft_strdup_two.c ft_strjoin_free.c ft_strndup.c print_lst.c utils.c
SRC_UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

SRC = $(SRC_CMD) $(SRC_ENV) $(SRC_EXC) $(SRC_HDL) $(SRC_MAIN) $(SRC_PARS) $(SRC_STRC) $(SRC_UTILS)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
	
=======
# Source files
SRCS	= $(SRC_DIR)cd.c \
			$(SRC_DIR)check_envp.c \
			$(SRC_DIR)check_tokens.c \
			$(SRC_DIR)copy_envp.c \
			$(SRC_DIR)create_cmd_list.c \
			$(SRC_DIR)dolar.c \
			$(SRC_DIR)echo.c \
			$(SRC_DIR)env.c \
			$(SRC_DIR)exe.c \
			$(SRC_DIR)execute_builtin.c \
			$(SRC_DIR)execute_commands.c \
			$(SRC_DIR)export.c \
			$(SRC_DIR)external_commands.c \
			$(SRC_DIR)finders.c \
			$(SRC_DIR)ft_free.c \
			$(SRC_DIR)ft_isspace.c \
			$(SRC_DIR)ft_strcat.c \
			$(SRC_DIR)ft_strcmp.c \
			$(SRC_DIR)ft_strcpy.c \
			$(SRC_DIR)ft_strdup_two.c \
			$(SRC_DIR)ft_strjoin_free.c \
			$(SRC_DIR)ft_strndup.c \
			$(SRC_DIR)handle_heredoc.c \
			$(SRC_DIR)input_analizes.c \
			$(SRC_DIR)main.c \
			$(SRC_DIR)pipeline.c \
			$(SRC_DIR)print_lst.c \
			$(SRC_DIR)prompt.c \
			$(SRC_DIR)pwd.c \
			$(SRC_DIR)quote_checker.c \
			$(SRC_DIR)quote_handle.c \
			$(SRC_DIR)redirection.c \
			$(SRC_DIR)set_envvar.c \
			$(SRC_DIR)set_envvar2.c \
			$(SRC_DIR)signal.c \
			$(SRC_DIR)strip_quotes.c \
			$(SRC_DIR)tokenization.c \
			$(SRC_DIR)type_tokens.c \
			$(SRC_DIR)unset.c \
			$(SRC_DIR)utils.c \
			
OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
>>>>>>> luiz

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(CMD_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ENV_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(HDL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(STRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

valgrind:
<<<<<<< HEAD
	valgrind --suppressions=readline.supp  --track-fds=all --leak-check=full --show-leak-kinds=all env -i ./minishell || true
=======
	valgrind --suppressions=readline.supp --track-fds=all --leak-check=full --show-leak-kinds=all ./minishell || true
>>>>>>> luiz

re: fclean all

.PHONY: all clean fclean re
