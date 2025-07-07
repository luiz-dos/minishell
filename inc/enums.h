/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:55:32 by luiz-dos          #+#    #+#             */
/*   Updated: 2025/07/04 18:56:01 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_types
{
	CMD,
	ARG,
	FILENAME,
	DELIM,
	PIPE,
	HEREDOC,
	APPEND_OUT,
	REDIR_OUT,
	REDIR_IN
};
enum e_markers
{
	N_SPACE = -32,
	N_DQUOTE = -34,
	N_SQUOTE = -39,
};

#endif /* ENUMS_H */