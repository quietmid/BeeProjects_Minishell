/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:57:38 by jlu               #+#    #+#             */
/*   Updated: 2024/07/03 18:49:40 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// need to check the right error_msg
# define ERR_QUOTES "syntax error unexpected EOF while look for matching ` "
# define ERR_SYNTAX "syntax error parse error near "
# define ERR_NL "syntax error near unexpected token 'newline'"

# define ERR_MALLOC "malloc unexpeectedly failed"
# define ERR_PIPE "unexpected error while opening pipe"
# define ERR_FORK "unexpected error while creating fork"
# define ERR_CMD "command not found"
# define ERR_NOFILE "No such file or directory"
# define ERR_HOME "cd: HOME not set"
# define ERR_OLDPWD "cd: OLDPWD not set"



typedef enum error
{
    XMALLOC,
    XPIPE,
    XFORK,
    XCMD,
    XNOFILE,
    XFD,
    XDUP,
    XCD,
    XCDHOME,
    XCDOLDPWD,
}   t_error;

#endif