/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:34:17 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 16:16:41 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_builtin(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE)
	{
		data->parent_in = dup(STDIN_FILENO);
		redir_in_fd(data, x);
	}
	if (is_redir(data, x, ">") == TRUE)
	{
		data->parent_out = dup(STDOUT_FILENO);
		redir_out_fd(data, x);
	}
	if (is_redir(data, x, ">>") == TRUE)
	{
		data->parent_out = dup(STDOUT_FILENO);
		redir_append_fd(data, x);
	}
}

void	restore_stdio(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE)
	{
		if (dup2(data->parent_in, STDIN_FILENO) < 0)
		{
			error(data, XDUP, 0);
		}
		close(data->parent_in);
	}
	if (is_redir(data, x, ">") == TRUE)
	{
		if (dup2(data->parent_out, STDOUT_FILENO) < 0)
			error(data, XDUP, 0);
		close(data->parent_out);
	}
	if (is_redir(data, x, ">>") == TRUE)
	{
		if (dup2(data->parent_out, STDOUT_FILENO) < 0)
			error(data, XDUP, 0);
		close(data->parent_out);
	}
	return ;
}

int	is_redir_x(t_data *data, int x, char *str)
{
	int	i;

	if (data->token[x].redir)
	{
		i = (data->token[x].redir_len - 1);
		while (i > 0)
		{
			if (ft_strcmp(data->token[x].redir[i][0], str) == 0)
				return (i);
			i--;
		}
		return (-1);
	}
	return (-1);
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
