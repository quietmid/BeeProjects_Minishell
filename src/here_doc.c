/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/06/24 20:11:45 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check for here_doc if it returns -1, no here_doc if its >= 0 then it means here doc found*/
// int    check_heredoc(t_data *data)
// {
//     int i;
//     int j;
//     char *ag;
//     t_token *t;

//     t = data->token;
//     i = 0;
//     while (i < data->cmd_count)
//     {
//         j = 0;
//         while (t[i].redir[j])
//         {
//             ag = t[i].redir[j][0];
//             if (ag && !ft_strncmp("<<", ag, 2))
//             {
//                 //here_doc = TRUE;
//                 printf("here_doc found\n");
//                 return (i);
//             }
//             j++;
//         }
//         i++;
//     }
//     return (-1);
// }
