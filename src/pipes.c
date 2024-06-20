/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/18 21:03:36 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirects(t_data *d, int x)
{
	if (d->cmd_count > 1 && d->token->redir[x] == NULL)
	{
		if (x == d->cmd_count -1)
		{
			dup2(d->pipe[x][1], STDOUT_FILENO);
		}
		else if (x < d->cmd_count -1)
		{
			dprintf(2, "skdfhlsflkh");
			dup2(d->pipe[x][1], STDOUT_FILENO);
			dup2(d->pipe[x - 1][0], STDIN_FILENO);
		}
		else if (x == d->cmd_count - 1)
		{
			dup2(d->pipe[x - 1][0], STDIN_FILENO);
		}
	}
	else
	{
		while (d->token->redir[x])
		{
			if (ft_strcmp(&d->token->redir[x][0], "<") == 0)
			{
				d->token->in = open(&d->token->redir[x][1], O_RDONLY);
				dup2(d->token->in, STDIN_FILENO);
				close(d->token->in);
			}
			else if (ft_strcmp(&d->token->redir[x][0], ">") == 0)
			{
				d->token->out = \
				open(&d->token->redir[x][1], O_CREAT | O_RDWR | O_TRUNC, 0644);
				dup2(d->token->out, STDOUT_FILENO);
				close(d->token->out);
			}
			else if (ft_strcmp(&d->token->redir[x][0], ">>") == 0)
			{
				d->token->out = \
				open(&d->token->redir[x][1], O_CREAT | O_APPEND | O_RDWR, 0644);
				dup2(d->token->out, STDOUT_FILENO);
				close(d->token->out);
			}
			x++;
		}
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
	}
}

void child_process(t_data *data, int x)
{
	ft_putstr_fd("went to child", 2);
	check_redirects(data, x);
	if (search_env(data, "PATH"))
	{
		data->path_cmd = find_path_cmd(data);
		if (!data->path_cmd)
			ft_putstr_fd("command not found", 2);
		env_to_arr(data);
		execve(data->path_cmd, &data->token->cmd[x], data->env_arr);
		// check if execve fails to free all mallocs otherwise its fine.
	}
}

void	create_forks(t_data *data)
{
	int	x;

	data->pid = (int *)malloc(sizeof(int) * data->cmd_count);
	if (!data->pid)
		printf("malloc fail"); // error fail
	x = 0;
	while (x < data->cmd_count)
	{
		data->pid[x] = fork();
		if (data->pid[x] < 0)
		{
			if (x != 0)
			{
				while (x >= 0)
					waitpid(data->pid[x], &data->status, 0);
				x--;
			}
			printf("forkerror"); //error
		}
		if (data->pid[x] == 0)
			child_process(data, x);
		x++;
	}
	if (data->cmd_count > 0)
	{
		x = 0;
		while (x < data->cmd_count)
		{
			close_pipes(data);
			waitpid(data->pid[x], &data->status, 0);
			x++;
		}
	}
}

void	create_pipes(t_data *data)
{
	int	x;
	int	pipe_count;

	pipe_count = data->cmd_count - 1;
	data->pipe = (int **)malloc(sizeof(int *) * (pipe_count));
	if (!data->pipe)
		printf("malloc fail"); // error fail
	x = 0;
	while (x < pipe_count)
	{
		data->pipe[x] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe[x])
			printf("malloc fail"); // error fail
		pipe(data->pipe[x]);
		if (data->pipe[x][0] < 0 || data->pipe[x][1] < 0)
			printf("error opening pipe"); // erro
		x++;
	}
}

