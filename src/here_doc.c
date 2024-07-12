/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/07/12 14:10:15 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sigint = 0;

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
            t->hd = 3;
            return (1);
        }
        i++;
    }
    return (0);
}

int    ft_hd(t_data *data, int i, int j)
{
    int hd;
    char *line;
    char *limiter;
    char *hdfile;
    
    printf("went to hd\n");
    hdfile = ft_itoa(i);
    if (!hdfile)
        error(data, XMALLOC, EXIT_FAILURE);
    limiter = data->token[i].redir[j][1];
    hd = open(hdfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (hd < 0)
		error(data, XHD, EXIT_FAILURE);
    signal_setup(SIG_HEREDOC); // just added
    while (1)
	{
        line = readline("> ");
        if (!line)
            break ;
        if (line && *line != '\0')
        {
		    if (ft_strcmp(line, limiter))
                ft_putendl_fd(line, hd);
            else if (!ft_strcmp(line, limiter))
                break;
        }
        if (g_sigint == 1)
            break ;
		free(line);
	}
    printf("out of the loop\n");
    if (g_sigint == 1)
    {
        printf("END\n");
        return (0);
    }
    free(hdfile);
    data->token[i].hd = hd;
    close(hd);
    return (1);
}

int    here_doc(t_data *data)
{
    int i;
    int j;
    t_token *t;

    t = data->token;

    i = 0;
    while (i < data->cmd_count)
    {
        j = 0;
        if (data->token[i].hd == 3)
        {
            while(t[i].redir[j])
            {
                if (!ft_strncmp("<<", t[i].redir[j][0], 2))
                {
                    if (!ft_hd(data, i, j))
                        return (0);
                }
                j++;
            }
        }
        i++;
    }
    return (1);
}
