/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:58:15 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 17:58:16 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

int	apply_last_redirs(int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			close(fd_in);
			return (-1);
		}
		close(fd_in);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(fd_out);
			return (-1);
		}
		close(fd_out);
	}
	return (0);
}

void	update_fd_values(t_redir *redir, int *fd_in, int *fd_out, int temp_fd)
{
	if (redir->type == REDIR_IN)
	{
		if (*fd_in != -1)
			close(*fd_in);
		*fd_in = temp_fd;
	}
	else if (redir->type == REDIR_OUT || redir->type == APPEND_OUT)
	{
		if (*fd_out != -1)
			close(*fd_out);
		*fd_out = temp_fd;
	}
}

int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->filename)
		return (-1);
	if (redir->type == REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
	{
		perror(redir->filename);
		set_questionvar(shell(), 1);
	}
	return (fd);
}

int	process_redirects(t_command *cmd, int *fd_in, int *fd_out)
{
	t_redir	*redir;
	int		temp_fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type >= APPEND_OUT && redir->type <= REDIR_IN)
		{
			temp_fd = open_redir_file(redir);
			if (temp_fd == -1)
				return (-1);
			update_fd_values(redir, fd_in, fd_out, temp_fd);
		}
		else if (redir->type == HEREDOC)
		{
			if (*fd_in != -1)
				close(*fd_in);
			*fd_in = cmd->heredoc_fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	handle_all_redirects(t_command *cmd)
{
	t_redir	*redir;
	int		fd_in;
	int		fd_out;

	redir = cmd->redirs;
	fd_in = -1;
	fd_out = -1;
	while (redir)
	{
		if (redir->type == HEREDOC && create_heredoc(cmd, redir) == -1)
		{
			cleanup_hd_in_pipeline(cmd);
			return (-1);
		}
		redir = redir->next;
	}
	if (process_redirects(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (apply_last_redirs(fd_in, fd_out));
}
