/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/26 17:37:18 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_redirects(t_data *d, int x)
// {
// 	if (redir_present(d,x) == FALSE)
// 	{
// 		if (x == 0)
// 		{
// 			dprintf(2, "to stdout\n");
// 			dup2(d->pipe[x][1], STDOUT_FILENO);
// 		}
// 		else if (x == d->cmd_count - 1)
// 		{
// 			dup2(d->pipe[x - 1][0], STDIN_FILENO);
// 		}
// 		else
// 		{
// 			dprintf(2, "to pipe\n");
// 			dup2(d->pipe[x][1], STDOUT_FILENO);
// 			dup2(d->pipe[x - 1][0], STDIN_FILENO);
// 		}
// 	}
// 	else
// 	{
// 		int x;
// 		x = 0;
// 		while (redir_present(d, x) == TRUE)
// 		{
// 			if (ft_strcmp(d->token->redir[x][0], "<") == 0)
// 			{
// 				d->token->in = open(d->token->redir[x][1], O_RDONLY);
// 				dup2(d->token->in, STDIN_FILENO);
// 				close(d->token->in);
// 			}
// 			else if (ft_strcmp(d->token->redir[x][0], ">") == 0)
// 			{
// 				d->token->out = 
// 				open(d->token->redir[x][1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 				dup2(d->token->out, STDOUT_FILENO);
// 				close(d->token->out);
// 			}
// 			else if (ft_strcmp(d->token->redir[x][0], ">>") == 0)
// 			{
// 				d->token->out = 
// 				open(d->token->redir[x][1], O_CREAT | O_APPEND | O_RDWR, 0644);
// 				dup2(d->token->out, STDOUT_FILENO);
// 				close(d->token->out);
// 			}
// 			x++;
// 		}
// 	}
// }

void child_process(t_data *data, int x)
{
	//ft_putstr_fd("went to child", 2);
	 
	if (data->cmd_count > 1)
	{
		dprintf(2, "went to redirect to pipe\n");
		redirect_to_pipe(data, x);
	}
	// if (data->token[x].redir)
	// {
	// 	dprintf(2, "went to redirect to redirect\n");
	// 	redirect_to_redir(data, x);
	// }
	if (search_env(data, "PATH"))
	{
		data->path_cmd = find_path_cmd(data, x);
		if (!data->path_cmd)
			ft_putstr_fd("FFFcommand not found", 2);
		env_to_arr(data);
		execve(data->path_cmd, data->token[x].cmd, data->env_arr);
		// check if execve fails to free all mallocs otherwise its fine.
		return  ;
	}
}


void	create_forks(t_data *data)
{
	int	x;

	data->pid = (int*)malloc(sizeof(int) * (data->cmd_count));
	if (!data->pid)
		printf("malloc fail"); // error fail
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
			printf("forkerror"); //error
		}
		if (data->pid[x] == 0)
		{
			dprintf(2, "child/pid: %d\n", x);
			child_process(data, x);
		}
		x++;
	}
	// x = 0;
	// dprintf(2, "PIPES: %d\n", data->pipe_count);
	// while(x < data->cmd_count)
	// {
	// 	dprintf(2,"went to closing");
	// 	close(data->pipe[x][1]);
	// 	close(data->pipe[x][0]);
	// 	x++;
	// }

}

void	create_pipes(t_data *data)
{
	int	x;

	data->pipe_count = data->cmd_count - 1;
	data->pipe = (int **)malloc(sizeof(int *) * (data->pipe_count));
	if (!data->pipe)
		printf("malloc fail"); // error fail
	x = 0;
	while (x < data->pipe_count)
	{
		data->pipe[x] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe[x])
			printf("malloc fail"); // error fail
		// pipe(data->pipe[x]);
		// if (data->pipe[x][0] < 0 || data->pipe[x][1] < 0)
		// 	printf("error opening pipe"); // erro
		x++;
	}
	x = 0;
	while (x < data->pipe_count)
	{
		if (pipe(data->pipe[x]) < 0)
			printf("error opening pipe"); // erro
		x++;
	}
}

