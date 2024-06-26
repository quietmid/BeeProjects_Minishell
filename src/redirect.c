
#include "minishell.h"

void	redirect_to_redir(t_data *data, int x)
{
	int i;
	
	i = 0;
	if (data->token[x].redir != NULL)
	{
		while (data->token[x].redir[i] != NULL)
		{
			dprintf(2, "went inside redir at cmd %d\n", x);
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
            close_pipes(data);
            //close(data->pipe[x][0]);
		}
		else if (x < (data->cmd_count - 1))
		{
			dprintf(2, "cmd % d IN from PIPE %d OUT to PIPE %d\n", x, x - 1, x);
			dup2(data->pipe[x - 1][0], STDIN_FILENO);
			dup2(data->pipe[x][1], STDOUT_FILENO);
            close_pipes(data);
			// close(data->pipe[x - 1][1]);
			// close(data->pipe[x][0]);
		}
		else if (x == (data->cmd_count - 1))
		{
			dprintf(2, "cmd %d IN from pipe %d\n", x ,x - 1);
			dup2(data->pipe[x - 1][0], STDIN_FILENO);
			close_pipes(data);
            //close(data->pipe[x - 1][1]);
		}
	}
	return ;
}