/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/23 17:30:43 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->cmd_count - 1))
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
	}
	return ;
}

void	create_forks(t_data *data)
{
	int	x;

	data->pid = (int *)malloc(sizeof(int) * (data->cmd_count));
	if (!data->pid)
		error(data, XMALLOC, EXIT_FAILURE);
	x = 0;
	while (x < data->cmd_count)
	{
		data->pid[x] = fork();
		if (data->pid[x] < 0)
		{
			if (data->pid[x] < 0)
			{
				while (x != 0)
					waitpid(data->pid[x], &data->status, 0);
				x--;
			}
			error(data, XFORK, EXIT_FAILURE);
		}
		else if (data->pid[x] == 0)
		{
			child_process(data, x);
		}
		x++;
	}
}

void	create_pipes(t_data *data)
{
	int	x;

	data->pipe_count = data->cmd_count - 1;
	data->pipe = (int **)malloc(sizeof(int *) * (data->pipe_count));
	if (!data->pipe)
		error(data, XMALLOC, EXIT_FAILURE);
	x = 0;
	while (x < data->pipe_count)
	{
		data->pipe[x] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe[x])
			error(data, XMALLOC, EXIT_FAILURE);
		pipe(data->pipe[x]);
		if (data->pipe[x][0] < 0 || data->pipe[x][1] < 0)
			error(data, XPIPE, EXIT_FAILURE);
		x++;
	}
}
