/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:01:07 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:56:12 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_var
{
	char			*content;
	char			*name;
	char			*value;
	bool			env;
	bool			exp;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct s_tokens
{
	char				*content;
	int					type;
	bool				double_quotes;
	bool				single_quotes;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;

typedef struct s_redir
{
	int					type; // in, out, append ou heredor
	char				*filename; // ou delimitador
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_redir				*redirs;
	int					heredoc_fd;
	pid_t				pid;
	bool				has_pipe;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char			*input;
	int				return_status; // $?
	char			**ev_array;
	t_var			*envvar;
	t_var			*envvar_export;
	t_tokens		*tokens;
	t_command		*commands;
	struct s_shell	*next;
	struct s_shell	*prev;
}	t_shell;

#endif /* STRUCTS_H */