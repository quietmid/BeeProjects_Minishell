/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/07/16 17:25:55 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sigint = 0;

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

static int hd_init(t_data *data, int i)
{
    int fd;

    data->token[i].hdfile = ft_itoa(i);
    if (!data->token[i].hdfile)
        error(data, XMALLOC, EXIT_FAILURE);
    fd = open(data->token[i].hdfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0)
		error(data, XHD, EXIT_FAILURE);
    return (fd);
}

static int hd_done(t_data *data, int hd, int i)
{
    if (g_sigint == 1)
    {
        unlink(data->token[i].hdfile);
        close(hd);
        g_sigint = 0;
        return (0);
    }
    data->token[i].hd = hd;
    return (1);
}

int    ft_hd(t_data *data, int i, int j)
{
    int hd;
    int stdin_backup;
    char *line;

    stdin_backup = safe_dup(STDIN_FILENO);
    hd = hd_init(data, i);
    set_signal_handler(SIGINT, heredoc_handler);
    while (1)
	{
		line = readline("> ");
        if (!line)
            break ;
        if (line && *line != '\0')
        {
            if (!ft_strcmp(line, data->token[i].redir[j][1]))
                break;
            line = check_expand(line, data);
            ft_putendl_fd(line, hd);
        }
		free(line);
	}
    free(line);
    safe_dup2(stdin_backup, STDIN_FILENO);
    // data->token[i].hd = hd; //put this in hd_done
    return (hd_done(data, hd, i));
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
