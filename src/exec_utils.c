/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:01:21 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 19:26:27 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
