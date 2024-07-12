/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:17:18 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/12 20:03:51 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_hd_fd(t_data *data, int x)
{
	int	i;

	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], "<<") == 0)
		{
			data->token->in = open(data->token[x].hdfile, O_RDONLY);
			if (data->token->in < 0)
			{
				unlink(data->token[x].hdfile);
				error_var(data, XFD, data->token[x].hdfile, 0);
			}
			if (dup2(data->token->in, STDIN_FILENO) < 0)
			{
				unlink(data->token[x].hdfile);
				error(data, XDUP, 0);
			}
			close(data->token->in);
		}
		i++;
	}
	unlink(data->token[x].hdfile);
}

void	redir_in_fd(t_data *data, int x)
{
	int	i;

	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], "<") == 0)
		{
			data->token->in = open(data->token[x].redir[i][1], O_RDONLY);
			if (data->token->in < 0)
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->in, STDIN_FILENO) < 0)
				error(data, XDUP, 0);
			close(data->token->in);
		}
		i++;
	}
}

void	redir_out_fd(t_data *data, int x)
{
	int	i;

	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], ">") == 0)
		{
			data->token->out = open(data->token[x].redir[i][1], \
				O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->token->out < 0)
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->out, STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
			close(data->token->out);
		}
		i++;
	}
}

void	redir_append_fd(t_data *data, int x)
{
	int	i;

	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], ">>") == 0)
		{
			data->token->out = open(data->token[x].redir[i][1], \
				O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->token->out < 0)
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->out, STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
			close(data->token->out);
		}
		i++;
	}
}
