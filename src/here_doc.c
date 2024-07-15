/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:17:23 by jlu               #+#    #+#             */
/*   Updated: 2024/07/15 19:09:12 by jlu              ###   ########.fr       */
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
// // when i exit with ctrl-d, the bad address caused leaks
// int    ft_hd(t_data *data, int i, int j)
// {
//     int hd;
//     // char *str;
//     char buf[512];
//     char tmp_buf[1];
//     char *limiter;
//     char *hdfile;
//     ssize_t bytes;
//     ssize_t t_bytes;

//     // printf("went to hd\n");
//     hdfile = ft_itoa(i);
//     if (!hdfile)
//         error(data, XMALLOC, EXIT_FAILURE);
//     limiter = ft_strjoin(data->token[i].redir[j][1], "\n");
//     hd = open(hdfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (hd < 0)
// 		error(data, XHD, EXIT_FAILURE);
//     // str = ft_safe_malloc(sizeof(char));
//     set_signal_handler(SIGINT, heredoc_handler);
//     t_bytes = 0;
//     while (1)
//     {
//         if (t_bytes == 0)
//             write (1, "> ", 2);
//         bytes = read(STDIN_FILENO, tmp_buf, 1);
//         if (bytes < 0)
//             break ;
//         if (bytes == 0)
//         {
//             if (t_bytes == 0)
//             {
//                 printf("\n");
//                 break ;
//             }
//             else
//                 continue ; 
//         }
//         buf[t_bytes] = tmp_buf[0];
//         t_bytes ++;
//         buf[t_bytes] = '\0';
//         if (tmp_buf[0] == '\n')
//         {
//             if (!ft_strcmp(buf, limiter))
//                 break ;
//             else
//             {
//                 // str = check_expand(buf, data);
//                 ft_putstr_fd(buf, hd);
//                 t_bytes = 0;
//             }
//         }
//     }
//     // printf("g_sigint: %d\n", g_sigint);
//     if (g_sigint == 1)
//     {
//         unlink(hdfile);
//         free(hdfile);
//         free(limiter);
//         // free(str);
//         close (hd);
//         g_sigint = 0;
//         return (0);
//     }
//     // free(str);
//     free(hdfile);
//     free(limiter);
//     data->token[i].hd = hd;
//     return (1);
// }

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

static void hd_done(t_data *data, int hd, int i)
{
    if (g_sigint == 1)
    {
        unlink(data->token[i].hdfile);
        close(hd);
        g_sigint = 0;
    }
    // return (0);
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
            {
                free(line);
                break;
            }
            line = check_expand(line, data);
            ft_putendl_fd(line, hd);
        }
		free(line);
	}
    safe_dup2(stdin_backup, STDIN_FILENO);
    if (g_sigint == 1)
    {
        hd_done(data, hd, i);
        return (0);
    }
    data->token[i].hd = hd;
    return (1);
}

// int    ft_hd(t_data *data, int i, int j)
// {
//     int hd;
//     char *line;
//     char *limiter;
//     char *hdfile;

//     hdfile = ft_itoa(i);
//     if (!hdfile)
//         error(data, XMALLOC, EXIT_FAILURE);
//     data->token[i].hdfile = ft_itoa(i);
//     if (!data->token[i].hdfile)
//         error(data, XMALLOC, EXIT_FAILURE);
//     limiter = data->token[i].redir[j][1];
//     hd = open(data->token[i].hdfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (hd < 0)
// 		error(data, XHD, EXIT_FAILURE);
//     set_signal_handler(SIGINT, heredoc_handler);
//     while (g_sigint == 0)
// 	{
// 		line = readline("> ");
//         if (!line)
//             break ;
//         if (line)
//         {
// 	        if (ft_strcmp(line, limiter))
//             {
//                 line = check_expand(line, data);
//                 ft_putendl_fd(line, hd);
//             }
//             else if (!ft_strcmp(line, limiter))
//             {
//                 free(line);
//                 break;
//             }
//         }
// 		free(line);
// 	}
//     if (g_sigint == 1)
//     {
//         unlink(hdfile);
//         free(hdfile);
//         free(limiter);
//         close (hd);
//         g_sigint = 0;
//         return (0);
//     }
//     data->token[i].hd = hd;
//     return (1);
// }

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
