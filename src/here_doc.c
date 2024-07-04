/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/07/04 17:29:19 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check for here_doc if it returns -1, no here_doc if its >= 0 then it means here doc found*/
int    check_heredoc(t_data *data)
{
    int i;
    int j;
    char *ag;
    t_token *t;

    data->hd = 0;
    t = data->token;
    i = 0;
    while (i < data->cmd_count)
    {
        j = 0;
        while (t[i].redir[j])
        {
            ag = t[i].redir[j][0];
            if (ag && !ft_strncmp("<<", ag, 2))
            {
                data->hd = 1;
                printf("here_doc found\n");
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
