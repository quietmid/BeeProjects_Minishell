/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:10:57 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/09 16:58:28 by pbumidan         ###   ########.fr       */
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
	return;
}

void redir_hd_fd(t_data *data, int x)
{
	int i;
	
	i = 0;
	while (data->token[x].redir[i])
	{
		if (ft_strcmp(data->token[x].redir[i][0], "<<") ==  0)
		{
			data->token->in = open(ft_itoa(x), O_RDONLY);
			if (data->token->in < 0)
			{
				unlink(ft_itoa(x));
				error_var(data, XFD, ft_itoa(x), 0);
			}
			if (dup2(data->token->in, STDIN_FILENO) < 0)
			{
				unlink(ft_itoa(x));
				error(data, XDUP, 0);	
			}
			close(data->token->in);
		}
		i++;
	}
	unlink(ft_itoa(x));
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
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->in, STDIN_FILENO) < 0)
				error(data, XDUP, 0);
			close(data->token->in);
			//dprintf(2, "cmd %d redir IN from %s\n",x, data->token[x].redir[i][1]);
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
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->out, STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
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
				error_var(data, XFD, data->token[x].redir[i][1], 0);
			if (dup2(data->token->out, STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
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
	if (data->token[x].redir)
	{
		while (data->token[x].redir[i])
		{
			if (ft_strcmp(data->token[x].redir[i][0], str) ==  0)
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

void	redirect_first(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
	//	if (is_redir(data, x, "<") == TRUE)
			redir_in_fd(data, x);
	//	if (is_redir(data, x, "<<") == TRUE)
			redir_hd_fd(data, x);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
	//	if (is_redir(data, x, ">") == TRUE )
			redir_out_fd(data, x);
	//	if (is_redir(data, x, ">>") == TRUE) 
			redir_append_fd(data, x);
	}
	else if (is_redir(data, x, ">") == FALSE || is_redir(data, x, ">>") == FALSE)
	{
		if (data->cmd_count > 1)
		{
			dprintf(2, "cmd %d OUT to pipe %d\n", x, x);
			if (dup2(data->pipe[x][1], STDOUT_FILENO) < 0)
				error(data, XDUP, 0);
			//close_pipes(data);
		}
	}
	close_pipes(data);
}

void	redirect_last(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
	//	if (is_redir(data, x, ">") == TRUE )
			redir_in_fd(data, x);
		//if ( is_redir(data, x, "<<") == TRUE)
			redir_hd_fd(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE || is_redir(data, x, "<<") == FALSE)
	{
		dprintf(2, "cmd %d IN from pipe %d\n", x ,x - 1);
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
		//close_pipes(data);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		//if (is_redir(data, x, ">") == TRUE )
			redir_out_fd(data, x);
		//if (is_redir(data, x, ">>") == TRUE) 
			redir_append_fd(data, x);
	}
	close_pipes(data);
}

void	redirect_middle(t_data *data, int x)
{
	if (is_redir(data, x, "<") == TRUE || is_redir(data, x, "<<") == TRUE)
	{
		//if (is_redir(data, x, ">") == TRUE )
			redir_in_fd(data, x);
	//	if ( is_redir(data, x, "<<") == TRUE)
			redir_hd_fd(data, x);
	}
	else if (is_redir(data, x, "<") == FALSE || is_redir(data, x, "<<") == FALSE)
	{
		dprintf(2, "cmd % d IN from PIPE %d OUT to PIPE %d\n", x, x - 1, x);
		if (dup2(data->pipe[x - 1][0], STDIN_FILENO) < 0)
			error(data, XDUP, 0);
		//close_pipes(data);
	}
	if (is_redir(data, x, ">") == TRUE || is_redir(data, x, ">>") == TRUE)
	{
		//if (is_redir(data, x, ">") == TRUE )
			redir_out_fd(data, x);
		//if (is_redir(data, x, ">>") == TRUE) 
			redir_append_fd(data, x);
	}
	else if (is_redir(data, x, ">") == FALSE || is_redir(data, x, ">>") == FALSE)
	{
		if (dup2(data->pipe[x][1], STDOUT_FILENO) < 0)
			error(data, XDUP, 0);
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
		if (dup2(data->parent_in, STDIN_FILENO) < 0)
			error(data, XDUP, 0);
		close(data->parent_in);
	}
	if (is_redir(data, x, ">") == TRUE)	
	{
		if (dup2(data->parent_out, STDOUT_FILENO)  < 0)
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
// void check_cmd(t_data *data, int x)
// {
// 	// if (data->token[x].cmd[0] == NULL || data->token[x].cmd[0][0] == '\0')
// 	// {
// 	// 	error_var(data, XCMD, data->token[x].cmd[0], 127);
// 	// }
// 	// if (cmds[0][0] == '/')
// 	// {
// 	// 	if (access(cmds[0], X_OK) != 0)
// 	// 	{
// 	// 		error_var(data, XCMD, data->token[x].cmd[0], 127);
// 	// 	}
// 	// }
// 	if (cmds[0][0] == '.')
// 	{
// 		if (access(cmds[0], X_OK) != 0)
// 		{
// 			error(pipex, cmd_err, cmds[0], 126);
// 		}
// 		if (open(cmds[0], O_RDONLY | O_DIRECTORY))
// 			error(pipex, dir_err, cmds[0], 126);
// 	}
// }

int	is_directory(char *cmd)
{
	struct stat	filestat;

	if (stat(cmd, &filestat) == 0)
	{
		if (S_ISDIR(filestat.st_mode))
			return (TRUE);
	}
	return (FALSE);
}

void child_process(t_data *data, int x)
{
	char *path;
	
	if (data->cmd_count > 1 || data->token[x].redir)
		redirect(data, x);
	env_to_arr(data);
	//check_cmd(data, x);
	if (data->token[x].cmd[0][0] == '/')
	{
		path = data->token[x].cmd[0];
		if (access(data->token[x].cmd[0], X_OK) != 0)
			error_var(data, XEXEC, data->token[x].cmd[0], 127);
	}
	if (data->token[x].cmd[0][0] == '.')
	{
		if (access(data->token[x].cmd[0], X_OK) != 0)
			error_var(data, XEXEC, data->token[x].cmd[0], 126);
		if (is_directory(data->token[x].cmd[0]) == TRUE)
			error_var(data, XDIR, data->token[x].cmd[0], 126);
	}
	else
	{
		if (search_env(data, "PATH"))
		{
			data->path_cmd = find_path_cmd(data, x);
			if (!data->path_cmd)
				error_var(data, XCMD, data->token[x].cmd[0], 127);
			path = data->path_cmd;
		}
		else
			error_var(data, XNOFILE, data->token[x].cmd[0], 127);
	}
	if (execve(path, data->token[x].cmd, data->env_arr) < 0)
		error(data, XEXEC, EXIT_FAILURE);
	free(path);
	free_data_all(data, 1);
	if (data->token[x].hd == 3)
		unlink(ft_itoa(x));
	return ;
}


void	create_forks(t_data *data)
{
	int	x;

	data->pid = (int*)malloc(sizeof(int) * (data->cmd_count));
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
			child_process(data, x);
		x++;
	}
	return ;
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

