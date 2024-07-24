/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:27:25 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/24 18:26:25 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_in_a(t_data *data, int x)
{
	if (is_redir_x(data, x, "<") > is_redir_x(data, x, "<<"))
	{
		redir_hd_fd(data, x);
		redir_in_fd(data, x);
	}
	else
	{
		redir_in_fd(data, x);
		redir_hd_fd(data, x);
	}
}

static void	redir_out_a(t_data *data, int x)
{
	if (is_redir_x(data, x, ">") > is_redir_x(data, x, ">>"))
	{
		redir_append_fd(data, x);
		redir_out_fd(data, x);
	}
	else
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
	}
}

void	redirect_first(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_in_a(data, x);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_a(data, x);
	}
	else if (is_redir(data, x, ">") == FALSE
		|| is_redir(data, x, ">>") == FALSE)
	{
		if (data->cmd_count > 1)
		{
			if (dup2(data->pipe[x][1], STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
		}
	}
	close_pipes(data);
}

void	redirect_last(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_in_a(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE
		|| is_redir(data, x, "<<") == FALSE)
	{
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_a(data, x);
	}
	close_pipes(data);
}

void	redirect_middle(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_in_a(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE
		|| is_redir(data, x, "<<") == FALSE)
	{
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_a(data, x);
	}
	else if (is_redir(data, x, ">") == FALSE
		|| is_redir(data, x, ">>") == FALSE)
	{
		if (dup2(data->pipe[x][1], STDOUT_FILENO) < 0)
			error(data, XDUP, 0);
	}
	close_pipes(data);
}
