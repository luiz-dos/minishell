#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "structs.h"
#include "libs.h"

	//pasta structs
//funcoes struct
t_shell 	*shell(void);
t_var		*env(void);
t_command	*cmmd(void);
t_tokens	*input(void);

/* execucao */
int		is_builtin(char *cmd);
void	execute_builtin(t_shell *data, t_command *cmd);
void	create_heredoc(t_command *current);
void	handle_parent_heredoc(t_command *current, int fd[2], pid_t pid);
void	handle_child_heredoc(t_command *current, int fd[2]);
void	exe(t_shell *data);
void	handle_pipeline(t_shell *data, t_command *cmd);
void    wait_for_children(t_shell *data, t_command *cmd, int cmd_count);
void	save_std_fileno(void);

/* parsing */
void	input_analizes(t_shell *data);
int		ft_quote_checker(char *input);
char	*normalize_input(char *input);
void	update_quote(char c, char *quote);
void	mark_input(char	*input);
int		mark_quotes(char *input, int *i);

/* signal */
void	ft_config_signals(int process_type);
void	hd_ft_handle_sigint(int signal);
void	ft_handle_sigint(int sig);
void	ft_ignore_some_signals(void);
void	ft_redefine_child_signals(void);

/* heredoc */
void	create_pipe(int fd[2]);
pid_t	create_fork(void);
void	write_line_to_pipe(char *line, int fd[2]);
void	loop_heredoc(t_command *current, int fd[2]);
void	close_fds(int fd[2]);

/* tokens */
void	create_tokens(char **tokens);
void	init_tokens(char **tokens);
void	ft_tokenadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_tokenlast(t_tokens *lst);
char	*del_nquotes(char *str);
int		count_quotes(char *str);
void	set_token_type(t_tokens *tokens);
int		check_tokens(t_shell *data);
int		check_tokens_two(t_tokens *token);

/* command list */
t_command	*create_cmd_list(t_tokens *tokens);
t_tokens	*handle_redir_out(t_command *cmd, t_tokens *token);
t_tokens	*handle_redir_in(t_command *cmd, t_tokens *token);
void		handle_argument(t_command *cmd, t_tokens *token);
void		handle_new_command(t_command **head, t_command **current, t_tokens *token);
void		clean_cmd_list(t_command *lst);

/* execute commands */
char	*get_command_path(char *cmd, char **envp);
void	exec_external_cmd(char **cmd);
char	**envvar_array(t_var *lst);

/* utils */
int		only_space(char *str);
int		check_envp(char **envp);
bool	check_options(char *option);
t_var	*find_envvar(t_var *lst, char *name);
char	*get_value(t_shell *data, char *name);
char	*get_pathname(void);
char	*color_to_prompt(char *prompt);

char	*ft_strjoin_free(const char *s1, const	char *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
char	*ft_strdup_two(const char *s, char c);
char	*ft_strndup(const char *s, size_t n);
bool	ft_isspace(char c);

/* redirect */
int		handle_redirects(t_command *cmd);
int 	redirect_input(char *file);
int		redirect_output(char *file);
int 	redirect_output_append(char *file);

void	mini_echo(char	**args, int fd);
void	mini_pwd(t_shell *data);
void	mini_env(t_var *lst);

/* export */
void	mini_export(t_command *cmd);
int		count_args(char **args);
void	print_export(t_shell *data);
void	sort_var(t_var *lst);
void	swap_nodes(t_var *current, t_var *next);
t_var	*create_lst_export(void);
t_var   *copy_var_node(t_var *envvar);

/* dolar */
void	expand_dolar(char **input);
int		inside_quotes(char	*str, size_t index);
int		handle_expansion(char **input, t_shell *data, int i);
char	*get_var_name(char *input, int index);
bool	is_sep(char sep);
char	*insert_into_str(char *str, int i, char *value, char *name);

/* unset */
void	unset(t_shell *data, char **args);
void	remove_envvar(t_var **lst, t_var *envvar);

/* cd */
void	cd(t_shell *data, char **args);
void	change_dir(char *dir, int flag_free, t_shell *data);
void	update_pwd(t_shell *data, char *dir);
char	*get_dir(char *arg, int *flag_free, t_shell *data);

/* lst */
t_var	*create_lst_envvar(char **envp);
void	add_var_back(t_var **lst, t_var *node);

/* set env*/
void	set_envvar(t_shell *data, char *name, char *value, int flag);
void	add_new_envvar(t_var *lst, char *name, char *value, int flag);
void	update_envvar(t_var *envvar, char *name, char *value);
char	*create_envvar_content(char *name, char *value);
void	set_shlvl(t_shell *data);
void	set_questionvar(t_shell *data, int return_status);
t_var	*min_env(void);

/* free*/
void	free_array(char **array);
void	free_lst(t_var *lst);
void	ft_tokenclear(t_tokens *lst);
void	free_exit(t_shell *data);

/* testes */
void	print_token_lst(t_tokens *lst);
void	print_cmd_lst(t_command *lst);

#endif /* FUNCTIONS_H */