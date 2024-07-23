/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:27:25 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/23 18:23:18 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_first(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_hd_fd(data, x);
		redir_in_fd(data, x);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
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

static void	redirect_last(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_in_fd(data, x);
		redir_hd_fd(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE
		|| is_redir(data, x, "<<") == FALSE)
	{
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
	}
	close_pipes(data);
}

static void	redirect_middle(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		redir_in_fd(data, x);
		redir_hd_fd(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE
		|| is_redir(data, x, "<<") == FALSE)
	{
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
	}
	else if (is_redir(data, x, ">") == FALSE
		|| is_redir(data, x, ">>") == FALSE)
	{
		if (dup2(data->pipe[x][1], STDOUT_FILENO) < 0)
			error(data, XDUP, 0);
	}
	close_pipes(data);
}

int	is_redir(t_data *data, int x, char *str)
{
	int	i;

	i = 0;
	if (data->token[x].redir)
	{
		while (data->token[x].redir[i])
		{
			if (ft_strcmp(data->token[x].redir[i][0], str) == 0)
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

void	redirect(t_data *data, int x)
{
	if (x < data->cmd_count)
	{
		if (x == 0)
			redirect_first(data, x);
		else if (x == (data->cmd_count - 1))
			redirect_last(data, x);
		else
			redirect_middle(data, x);
	}
	close_pipes(data);
	return ;
}
