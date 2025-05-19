NAME 		= libft.a
CFLAGS		= -Wall -Wextra -Werror -I../include
CC			= cc
RM			= rm -rf
CREATE		= ar rc
INDEXLIB	= ranlib

SRC_DIR		= .
OBJ_DIR		= objs

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
				ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_front.c \
				ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				analyze_identifier.c decimal_to_hex.c ft_unsigned_itoa.c \
				handle_conversion.c handle_field_width.c handle_flag.c \
				handle_precision.c init.c print_char.c print_fzero.c \
				print_hex_two.c print_hex.c print_int_three.c print_int_two.c \
				print_int.c print_pointer.c print_specifier.c print_string.c \
				print_unsigned_int.c ft_putstr_reverse_fd.c get_whitespace.c \
				isconversion.c isflag.c print_flag.c ft_printf.c \
				get_next_line.c get_next_line_utils.c


OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@${CREATE} ${NAME} ${OBJS}
	@${INDEXLIB} ${NAME}

all: ${NAME}

clean:
	@${RM} ${OBJ_DIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re
