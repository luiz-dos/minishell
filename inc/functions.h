/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:01:09 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/06 17:29:51 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"
# include "libs.h"
# include "enums.h"

extern int	g_sig;

/* singleton */
t_shell		*shell(void);

/* execucao */
void		execute_commands(t_command *cmd);
int			has_redir(t_command *cmd, int *stdin_bkp, int *stdout_bkp);
int			is_builtin(char *cmd);
void		execute_builtin(t_shell *data, t_command *cmd);
void		single_command(t_command *cmd);
void		external_command(t_command *cmd, int *stdin_bkp, int *stdout_bkp, \
	int redir_result);

/* redirect */
int			handle_all_redirects(t_command *cmd);
int			process_redirects(t_command *cmd, int *fd_in, int *fd_out);
int			open_redir_file(t_redir *redir);
void		update_fd_values(t_redir *redir, int *fd_in, int *fd_out, \
	int temp_fd);
int			apply_last_redirs(int fd_in, int fd_out);

/* pipeline */
void		handle_pipeline(t_command *cmd);
void		child_pipeline(t_command *cmd, int fd[2], int prev_fd);
int			handle_redir_in_pipeline(t_command *cmd);
void		update_heredoc_fd(t_command *cmd, int *fd_in);
void		update_pipe_descriptors(int *prev_fd, int fd[2], \
	t_command *current);
void		wait_for_children(t_shell *data, t_command *cmd, int cmd_count);
int			has_heredoc_redir(t_command *cmd);
int			has_in_redir(t_command *cmd);
int			has_out_redir(t_command *cmd);
int			create_hd_in_pipeline(t_command *cmd);
void		cleanup_hd_in_pipeline(t_command *cmd);

/* parsing */
void		input_analizes(t_shell *data);
int			ft_quote_checker(char *input);
char		*normalize_input(char *input);
void		update_quote(char c, char *quote);
void		mark_input(char	*input);
int			mark_quotes(char *input, int *i);

/* signal */
void		handle_sigint_main(int sig);
void		handle_sigint_heredoc(int sig);
void		set_sig_main(void);
void		set_sig_heredoc(void);
void		set_sig_ignore(void);
void		set_sig_child(void);

/* heredoc */
int			create_heredoc(t_command *current, t_redir *redir);
void		create_pipe(int fd[2]);
pid_t		create_fork(void);
void		child_heredoc(t_redir *redir, int fd[2]);
void		write_line_to_pipe(char *line, int fd[2]);
void		loop_heredoc(t_redir *redir, int fd[2]);
void		close_fds(int fd[2]);

/* tokens */
void		create_tokens(char **tokens);
void		init_tokens(char **tokens);
void		ft_tokenadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_tokenlast(t_tokens *lst);
char		*del_nquotes(char *str);
int			count_quotes(char *str);
void		set_token_type(t_tokens *tokens);
int			check_tokens(t_shell *data);
int			check_tokens_two(t_tokens *token);

/* command list */
t_command	*create_cmd_list(t_tokens *tokens);
void		create_cmd_list_two(t_command *current_cmd);
t_tokens	*handle_redir(t_command *cmd, t_tokens *token);
void		handle_argument(t_command *cmd, t_tokens *token);
void		handle_new_command(t_command **head, t_command **current, \
	t_tokens *token);
void		clean_cmd_list(t_command *lst);

/* execute commands */
char		*get_command_path(char *cmd, char **envp);
void		analize_ext_cmd(char **cmd);
void		exec_ext_cmd(char *command_path, char **cmd, char **env_var);
char		**envvar_array(t_var *lst);

/* utils */
int			only_space(char *str);
int			check_envp(char **envp);
bool		check_options(char *option);
t_var		*find_envvar(t_var *lst, char *name);
char		*get_value(t_shell *data, char *name);
char		*get_pathname(void);
char		*color_to_prompt(char *prompt);

char		*ft_strjoin_free(const char *s1, const	char *s2);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strdup_two(const char *s, char c);
char		*ft_strndup(const char *s, size_t n);

/* builtins */
void		mini_echo(char	**args, int fd);
void		mini_pwd(t_shell *data);
void		mini_env(char **args);
void		mini_exit(char **args);
int			is_numeric_arg(char *str);

/* export */
void		mini_export(t_command *cmd);
void		not_valid(t_command *cmd, int i);
int			is_valid_identifier(char *str);
void		check_value(t_command *cmd, char **var_name, char **var_value, \
	int i);
void		check_var_name(t_command *cmd, char *var_name, char *var_value, \
	int i);
int			count_args(char **args);
void		print_export(t_shell *data);
void		sort_var(t_var *lst);
void		swap_nodes(t_var *current, t_var *next);
t_var		*create_lst_export(void);
t_var		*copy_var_node(t_var *envvar);

/* dolar */
void		expand_dolar(char **input);
int			inside_quotes(char	*str, size_t index);
int			handle_expansion(char **input, t_shell *data, int i);
char		*get_var_name(char *input, int index);
bool		is_sep(char sep);
char		*insert_into_str(char *str, int i, char *value, char *name);

/* unset */
void		unset(t_shell *data, char **args);
void		remove_envvar(t_var **lst, char *var_name);

/* cd */
void		cd(t_shell *data, char **args);
void		change_dir(char *dir, int flag_free, t_shell *data);
void		update_pwd(t_shell *data, char *dir);
char		*get_dir(char *arg, int *flag_free);

/* lst */
t_var		*create_lst_envvar(char **envp);
void		add_var_back(t_var **lst, t_var *node);

/* set env*/
void		set_envvar(t_shell *data, char *name, char *value, int flag);
void		add_new_envvar(t_var *lst, char *name, char *value, int flag);
void		update_envvar(t_var *envvar, char *name, char *value);
char		*create_envvar_content(char *name, char *value);
void		set_shlvl(t_shell *data);
void		set_questionvar(t_shell *data, int return_status);
t_var		*min_env(void);

/* free*/
void		free_array(char **array);
void		free_lst(t_var *lst);
void		ft_tokenclear(t_tokens *lst);
void		clean_redir(t_command *cmd);
void		free_exit(t_shell *data, int exit_code);
void		close_remaining_fds(void);
void		free_str(char *var_name, char *var_value);

#endif /* FUNCTIONS_H */