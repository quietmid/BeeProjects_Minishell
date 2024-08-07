/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:57:38 by jlu               #+#    #+#             */
/*   Updated: 2024/07/25 18:39:22 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// need to check the right error_msg
# define ERR_QUOTES "syntax error unexpected EOF while look for matching ` "
# define ERR_SYNTAX "syntax near unexpected token ` "

# define ERR_MALLOC "malloc unexpectedly failed"
# define ERR_PIPE "unexpected error while opening pipe"
# define ERR_FORK "unexpected error while creating fork"
# define ERR_EXEC "unexpected error while executing command"
# define ERR_HD "unexpected error while creating heredoc temp file"
# define ERR_CWD "unexpected error while executing cwd"
# define ERR_EXP "not a valid identifier"

# define ERR_CMD ": command not found"
# define ERR_NOFILE ": No such file or directory"
# define ERR_HOME "cd: HOME not set"
# define ERR_OLDPWD "cd: OLDPWD not set"
# define ERR_DIR ": Is a directory"
# define ERR_PERM ": Permission Denied"

typedef enum error
{
	XSYNTAX,
	XMALLOC,
	XPIPE,
	XFORK,
	XEXEC,
	XCMD,
	XNOFILE,
	XFD,
	XDUP,
	XCD,
	XCDHOME,
	XCDOLDPWD,
	XDIR,
	XHD,
	XCWD,
	XEXP,
	XPERM,
	XARG,
}	t_error;

#endif
