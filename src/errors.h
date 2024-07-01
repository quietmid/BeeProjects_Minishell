/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:57:38 by jlu               #+#    #+#             */
/*   Updated: 2024/07/01 20:33:15 by pbumidan         ###   ########.fr       */
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


typedef enum error
{
    e_malloc,
    e_pipe,
    e_fork,
}   t_error;

#endif