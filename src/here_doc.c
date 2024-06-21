/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/06/20 21:40:11 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check for here_doc if it returns -1, no here_doc if its >= 0 then it means here doc found*/

// int    check_heredoc(t_data *data)
// {
//     int i;
//     t_token *t;

//     t = data->token;
//     while (t->redir[i])
//     {
//         if (t->redir[i][0][0] == '>' && t->redir[i][0][1] == '>' )
//         {
//             //here_doc = TRUE;
//             return (i);
//         }
//     }
//     return (-1);
// }