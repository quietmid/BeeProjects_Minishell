/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/17 17:32:48 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_creator(t_data *data)
{
	int	x;

	data->pipe = (int **)malloc(data->cmd_count * sizeof(int *));
	if (!data->pipe)
		printf("malloc fail"); // error fail
	x = 0;
	while (x < data->cmd_count)
	{
		data->pipe[x] = (int *)malloc(2 * sizeof(int));
		if (!data->pipe[x])
			printf("malloc fail"); // error fail
		x++;
	}
	x = 0;
	while (x < data->cmd_count)
	{
		pipe(data->pipe[x]);
		if (data->pipe[x][0] < 0 || data->pipe[x][1] < 0)
			printf("error opening pipe"); // error
		x++;
	}
	data->pid = (int *)malloc(sizeof(int) * data->cmd_count);
	if (!data->pid)
		printf("malloc fail"); // error fail
}

void	the_piper(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			printf("errrorrrr"); //errorr
		if (data->pid[i] == 0)
		printf("to child process");
			//child_process(data, i);
	}
}

