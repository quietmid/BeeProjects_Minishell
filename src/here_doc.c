/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/07/05 19:20:56 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check for here_doc if it returns -1, no here_doc if its >= 0 then it means here doc found*/
int    check_heredoc(t_token *t)
{
    int i;
    char *ag;

    i = 0;
    while (i < t->redir_len)
    {
        ag = t->redir[i][0];
        if (ag && !ft_strncmp("<<", ag, 2))
        {
            t->hd = 1;
            return (1);
        }
        i++;
    }
    return (0);
}
