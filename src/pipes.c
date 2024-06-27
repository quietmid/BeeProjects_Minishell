/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/27 17:06:33 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void redir_in_fd(t_data *data, int x)
{
	int i;
	
	i = 0;
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
		i++;
	}
}

void redir_out_fd(t_data *data, int x)
{
	int i;
	
	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], ">") == 0)
		{
			data->token->out = open(data->token[x].redir[i][1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->token->out < 0)
				printf("error, permission");
			if (dup2(data->token->out, STDOUT_FILENO) < 0)
				printf("duperror");
			close(data->token->out);
			dprintf(2, "cmd %d redir OUT to %s\n",x, data->token[x].redir[i][1]);
		}
		i++;
	}
}

void redir_append_fd(t_data *data, int x)
{
	int i;
	
	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], ">>") == 0)
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

int is_redir(t_data *data, int x, char *str)
{
	int i;
	
	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], str) ==  0)
			return (TRUE);
		i++;
	}
	return (FALSE);
	
}

// void	redirect_to_redir(t_data *data, int x)
// {
// 	int i;
	
// 	i = 0;
// 	if (data->token[x].redir[i] != NULL)
// 	{
// 		dprintf(2, "GGGGGGGGGGGGGGGGGGGGGGGGGGGG\n");
// 		while (data->token[x].redir[i])
// 		{
// 			if (ft_strcmp(data->token[x].redir[i][0], "<") ==  0)
// 			{
// 				data->token->in = open(data->token[x].redir[i][1], O_RDONLY);
// 				if (data->token->in < 0)
// 					printf("error, permission");
// 				if (dup2(data->token->in, STDIN_FILENO) < 0)
// 					printf("duperror");
// 				close(data->token->in);
// 				dprintf(2, "cmd %d redir IN from %s\n",x, data->token[x].redir[i][1]);
// 			}
// 			else if (ft_strcmp(data->token[x].redir[i][0], ">") == 0)
// 			{
// 				data->token->out = open(data->token[x].redir[i][1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 				if (data->token->out < 0)
// 					printf("error, permission");
// 				if (dup2(data->token->out, STDOUT_FILENO) < 0)
// 					printf("duperror");
// 				close(data->token->out);
// 				dprintf(2, "cmd %d redir OUT to %s\n",x, data->token[x].redir[i][1]);
// 			}
// 			else if (ft_strcmp(data->token[x].redir[i][0], ">>") == 0)
// 			{
// 				data->token->out = open(data->token[x].redir[i][1], O_CREAT | O_RDWR | O_APPEND, 0644);
// 				if (data->token->out < 0)
// 					printf("error, permission");
// 				if (dup2(data->token->out, STDOUT_FILENO) < 0)
// 					printf("duperror");
// 				close(data->token->out);
// 				dprintf(2, "cmd %d redir OUT to %s\n", x, data->token[x].redir[i][1]);
// 			}	
// 			i++;
// 		}
// 	}
// }

void	redirect_first(t_data *data, int x)
{
	redir_in_fd(data, x);
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
	}
	else
	{
		dprintf(2, "cmd %d OUT to pipe %d\n", x, x);
		dup2(data->pipe[x][1], STDOUT_FILENO);
	}
	close_pipes(data);
}

void	redirect_last(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE)
	{
		redir_in_fd(data, x);
	}
	else
	{
		dprintf(2, "cmd %d IN from pipe %d\n", x ,x - 1);
		dup2(data->pipe[x - 1][0], STDIN_FILENO);
	}
	redir_out_fd(data, x);
	redir_append_fd(data, x);
	close_pipes(data);
}

void	redirect_middle(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE)
	{
		redir_in_fd(data, x);
	}
	else
	{
		dprintf(2, "cmd % d IN from PIPE %d OUT to PIPE %d\n", x, x - 1, x);
		dup2(data->pipe[x - 1][0], STDIN_FILENO);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		redir_out_fd(data, x);
		redir_append_fd(data, x);
	}
	else
	{
		dup2(data->pipe[x][1], STDOUT_FILENO);	
	}
	close_pipes(data);
}

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
	return ;
}

void	restore_stdio(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE)
	{
		dup2(data->parent_in, STDIN_FILENO);
		close(data->parent_in);
	}
	if (is_redir(data, x, ">") == TRUE)	
	{
		dup2(data->parent_out, STDOUT_FILENO);
		close(data->parent_out);
	}
	if (is_redir(data, x, ">>") == TRUE)
	{
		dup2(data->parent_out, STDOUT_FILENO);
		close(data->parent_out);
	}	
	return ;
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
			redirect_last(data, x);
	}
}

void child_process(t_data *data, int x)
{
	//ft_putstr_fd("went to child", 2);
	// data->token->in = dup(STDIN_FILENO);
	// data->token->out = dup(STDOUT_FILENO);
	if (data->cmd_count > 1 || data->token[x].redir[0] != NULL)
		redirect(data, x);
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

