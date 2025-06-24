#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_var
{
	char			*content;
	char			*name;
	char			*value;
	bool			env;
	bool			exp;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct	s_tokens
{
	char				*content;
	int					type;
	bool				double_quotes;
	bool				single_quotes;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;

typedef struct	s_redir
{
	int					type; // in, out, append ou heredor
	char				*filename; // ou delimitador
	struct s_redir		*next;
}	t_redir;

typedef struct	s_command
{
	char				*cmd;
	char				**args;
	char				*infile;
	t_redir				*redirs;
	char				*heredoc_delim;
	bool				has_heredoc;
	int					heredoc_fd;
	pid_t				heredoc_pid;
	pid_t				pid; 
	bool				has_pipe;
	int					pipe_fd[2];
	struct s_command	*next;
}	t_command;

enum e_types
{
	CMD,
	ARG,
	FILENAME,
	DELIM,
	PIPE,
	HEREDOC, // <<
	APPEND_OUT, // >>
	REDIR_OUT, // >
	REDIR_IN // <
};

enum e_markers
{
	N_SPACE = -32,
	N_DQUOTE = -34,
	N_SQUOTE = -39,
};

typedef struct	s_shell
{
	char			*input;
	int				signal;
	int				return_status; // $?
	int				std_fileno[2];
	int				save_in;
	int				save_out;
	char			**ev_array;
	t_var			*envvar;
	t_var			*envvar_export;
	t_tokens		*tokens;
	t_command		*commands;
	struct	s_shell	*next;
	struct	s_shell	*prev;
}	t_shell;

#endif /* STRUCTS_H */