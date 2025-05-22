NAME	= minishell
CC		= cc
CFLAGS 	=  -Wall -Wextra -Werror -g
RM		= rm -f

# Directories
SRC_DIR = src/
OBJ_DIR = obj/

# Libraries
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a
LIBS		= -lreadline

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

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

valgrind:
	valgrind --suppressions=readline.supp  --track-fds=all --leak-check=full --show-leak-kinds=all ./minishell || true

re: fclean all

.PHONY: all clean fclean re