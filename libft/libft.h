/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:18:34 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/05/21 15:55:19 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif /* BUFFER_SIZE */

/* using an int as a boolean */
typedef int				t_bool;

/* named constants */
enum
{
	B_FALSE = 0,
	B_TRUE = 1
};

/* flags bonus */
typedef struct s_flags
{
	t_bool				minus;
	t_bool				plus;
	t_bool				hash;
	t_bool				zero;
	t_bool				space;
}						t_flags;

/* specifiers */
typedef struct s_specs
{
	t_bool				c;
	t_bool				s;
	t_bool				p;
	t_bool				d;
	t_bool				i;
	t_bool				u;
	t_bool				x;
	t_bool				upper_x;
	t_bool				percent;
}						t_specs;

/* data format */
typedef struct s_data_format
{
	t_flags				*flags;
	t_specs				*cspecs;
	int					field_w;
	int					precision;
	int					bytes;
	t_bool				error;
}						t_data_format;

/* string data */
typedef struct s_str
{
	int					pos;
	int					bytes;
	const char			*str;
	t_bool				error;
}						t_str;

/* Libft Node */
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

/* libft */
int						ft_atoi(const char *nptr);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
char					*ft_itoa(int n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						ft_tolower(int c);
int						ft_toupper(int c);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

/* printf */
int						ft_printf(const char *format, ...);
void					ft_printf_two(t_str *data, va_list args);
void					putchar_byte(t_str *data);
void					putchar_percent(t_str *data);
void					analyze_identifier(t_str *data, va_list args);
t_data_format			*init(t_data_format *data_f);
void					init_flags(t_data_format *data_f);
void					init_cspecs(t_data_format *data_f);
void					analyze_identifier_two(t_str *data,
							t_data_format *data_f);
t_bool					isflag(char c);
void					handle_flag(t_str *data, t_data_format *data_f);
void					handle_field_width(t_str *data, t_data_format *data_f);
void					handle_precision(t_str *data, t_data_format *data_f);

t_bool					isconversion(char c);
void					handle_conversion(t_str *data, t_data_format *data_f);
void					print_specifier(t_str *data, t_data_format *data_f,
							va_list args);
void					print_char(t_str *data, t_data_format *data_f, char c);
void					print_char_field_w(t_data_format *data_f, char c);
void					print_space_byte(t_data_format *data_f);
void					print_string(t_str *data, t_data_format *data_f,
							char *s);
void					print_fprecision(t_data_format *data_f, char *s,
							t_bool str_null);
int						get_whitespace(t_data_format *data_f, char *s);
void					print_fprecision_two(t_data_format *data_f, char *s,
							int whitespace);
void					print_noprecision(t_data_format *data_f, char *s);
void					print_pointer(t_str *data, t_data_format *data_f,
							unsigned long long int num);
unsigned long long int	ft_numlen_three(unsigned long long int n);
char					*decimal_to_hex(t_data_format *data_f,
							unsigned long long int num,
							unsigned long long int len_num);
char					*decimal_to_hex_two(t_data_format *data_f, char *hex,
							unsigned long long int num);
void					print_pointer_two(t_data_format *data_f, char *num_hex,
							int whitespace);
void					ft_putstr_reverse_fd(char *s, int fd);
void					print_int(t_str *data, t_data_format *data_f, int num);
void					print_fminus_fplus(t_data_format *data_f,
							char *str_num);
void					print_fplus_plus(t_data_format *data_f, char *str_num);
void					print_plus_byte(t_data_format *data_f);
void					print_zero_byte(t_data_format *data_f);
void					print_fminus_neg(t_data_format *data_f, char *str_num);
void					print_fminus_posi(t_data_format *data_f, char *str_num);
void					print_int_two(t_data_format *data_f, char *str_num);
void					print_fzero(t_data_format *data_f, char *str_num);
void					print_fzero_fplus(t_data_format *data_f, char *str_num);
void					print_fzero_fspace(t_data_format *data_f,
							char *str_num);
void					print_fzero_only(t_data_format *data_f, char *str_num);
void					print_no_fminus(t_data_format *data_f, char *str_num,
							int count_bytes);
void					print_posi(t_data_format *data_f, char *str_num,
							int count_bytes);
void					print_fplus_plus_two(t_data_format *data_f,
							char *str_num, int count_bytes);
void					print_neg(t_data_format *data_f, char *str_num,
							int count_bytes);
void					print_unsigned_int(t_str *data, t_data_format *data_f,
							unsigned int num);
char					*ft_unsigned_itoa(unsigned int n);
unsigned int			ft_numlen_two(unsigned int n);
void					print_hex(t_str *data, t_data_format *data_f,
							unsigned int num);
void					print_hex_two(t_data_format *data_f, char *str_num,
							int whitespace);
void					print_hex_fzero(t_data_format *data_f, char *str_num,
							int whitespace);
void					print_hex_fminus(t_data_format *data_f, char *str_num,
							int whitespace);
void					print_hex_only(t_data_format *data_f, char *str_num,
							int whitespace);
void					print_0x(t_data_format *data_f);
void					precision_is_zero(t_data_format *data_f);
void					handle_num_zero(t_data_format *data_f, int num);
void					handle_num_zero_two(t_data_format *data_f,
							unsigned int num);

/* get_next_line */
char					*get_next_line(int fd);
int						ft_strlen_gnl(char *s);
char					*ft_line(char *line, char *buffer);
void					ft_handle_buffer(char *buffer, int *found_newline);

#endif /* LIBFT_H */
