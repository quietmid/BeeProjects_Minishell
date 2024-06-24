/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/24 19:36:40 by jlu              ###   ########.fr       */
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
void	redirect_to_redir(t_data *data, int x)
{
	int i;
	
	i = 0;
	if (data->token[x].redir[i] != NULL)
	{
		while (data->token[x].redir[i])
		{
			if (ft_strcmp(data->token[x].redir[i][0], "<") ==  0)
			{
				data->token->in = open(data->token[x].redir[i][1], O_RDONLY);
				if (data->token->in < 0)
					printf("error, permission");
				if (dup2(data->token->in, STDIN_FILENO) < 0)
					printf("duperror");
				close(data->token->in);
				dprintf(2, "cmd %d redir IN from %s\n",x, data->token[x].redir[i][1]);

				
			}
			else if (ft_strcmp(data->token[x].redir[i][0], ">") == 0)
			{
				data->token->out = open(data->token[x].redir[i][1], O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (data->token->out < 0)
					printf("error, permission");
				if (dup2(data->token->out, STDOUT_FILENO) < 0)
					printf("duperror");
				close(data->token->out);
				dprintf(2, "cmd %d redir OUT to %s\n",x, data->token[x].redir[i][1]);
			}
			else if (ft_strcmp(data->token[x].redir[i][0], ">>") == 0)
			{
				data->token->out = open(data->token[x].redir[i][1], O_CREAT | O_RDWR | O_APPEND, 0644);
				if (data->token->out < 0)
					printf("error, permission");
				if (dup2(data->token->out, STDOUT_FILENO) < 0)
					printf("duperror");
				close(data->token->out);
				dprintf(2, "cmd %d redir OUT to %s\n", x, data->token[x].redir[i][1]);
			}	
			i++;
		}
	}
}

void	redirect_to_pipe(t_data *data, int x)
{
	if (data->cmd_count > 1)
	{
		if (x == 0)
		{
			dprintf(2, "cmd %d OUT to pipe %d\n", x, x);
			dup2(data->pipe[x][1], STDOUT_FILENO);
			close(data->pipe[x][0]);
		}
		else if (x == (data->cmd_count - 1))
		{
			dprintf(2, "cmd %d IN from pipe %d\n", x ,x - 1);
			dup2(data->pipe[x - 1][0], STDIN_FILENO);
			close(data->pipe[x - 1][1]);
		}
		else
		{
			dup2(data->pipe[x - 1][0], STDIN_FILENO);
			dup2(data->pipe[x][1], STDOUT_FILENO);
			dprintf(2, "cmd % d IN from PIPE %d OUT to PIPE %d\n", x, x - 1, x);
			close(data->pipe[x - 1][1]);
			close(data->pipe[x][0]);
		}
	}
}

void child_process(t_data *data, int x)
{
	//ft_putstr_fd("went to child", 2);
	// data->token->in = dup(STDIN_FILENO);
	// data->token->out = dup(STDOUT_FILENO);
	if (data->cmd_count > 1 && data->token[x].redir[0] == NULL)
		redirect_to_pipe(data, x);
	else
		redirect_to_redir(data, x);
	if (search_env(data, "PATH"))
	{
		data->path_cmd = find_path_cmd(data, x);
		if (!data->path_cmd)
			ft_putstr_fd("FFFcommand not found", 2);
		env_to_arr(data);
		execve(data->path_cmd, &data->token[x].cmd[0], data->env_arr);
		// check if execve fails to free all mallocs otherwise its fine.
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
		pipe(data->pipe[x]);
		if (data->pipe[x][0] < 0 || data->pipe[x][1] < 0)
			printf("error opening pipe"); // erro
		x++;
	}
}

