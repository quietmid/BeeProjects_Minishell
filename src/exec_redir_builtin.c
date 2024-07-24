/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:34:17 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/24 16:22:53 by pbumidan         ###   ########.fr       */
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
			error(data, XDUP, 0);
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
