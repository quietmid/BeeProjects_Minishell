/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:17:18 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 16:15:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_error(t_data *data, t_error code, int x)
{
	if (code == XDUP)
	{
		unlink(data->token[x].hdfile);
		error(data, XDUP, 0);
	}
	if (code == XFD)
	{
		unlink(data->token[x].hdfile);
		error_var(data, XFD, data->token[x].hdfile, 0);
	}
}

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
				unlink_error(data, XFD, x);
			if (data->token[x].cmd && data->ms_stat == 0)
			{
				if (dup2(data->token->in, STDIN_FILENO) < 0)
					unlink_error(data, XDUP, x);
			}
			if (data->token->in > 0)
				close(data->token->in);
		}
		i++;
	}
	if (data->token[x].hd == 3)
	{
		unlink(data->token[x].hdfile);
		free(data->token[x].hdfile);
	}
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
			{
				error_var(data, XFD, data->token[x].redir[i][1], 1);
			}
			if (data->token[x].cmd && data->ms_stat == 0)
			{
				if (dup2(data->token->in, STDIN_FILENO) < 0)
					error(data, XDUP, 0);
			}
			if (data->token->in > 0)
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
				error_var(data, XFD, data->token[x].redir[i][1], 1);
			if (data->token[x].cmd && data->ms_stat == 0)
			{
				if (dup2(data->token->out, STDOUT_FILENO) < 0)
					error(data, XDUP, 0);
			}
			if (data->token->out > 0)
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
				error_var(data, XFD, data->token[x].redir[i][1], 1);
			if (data->token[x].cmd && data->ms_stat == 0)
			{
				if (dup2(data->token->out, STDOUT_FILENO) < 0)
					error(data, XDUP, 0);
			}
			if (data->token->out > 0)
				close(data->token->out);
		}
		i++;
	}
}
