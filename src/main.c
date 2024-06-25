/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/25 17:37:49 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* support find_path_cmd fxn (2/2)
*/
char	**prepare_paths(t_env *env)
{
	char	**paths;
	char	**res;
	char	*tmp;
	int		x;

	paths = ft_split(env->value, ':');
	// if (!paths)
	// 	mallocerr
	res = (char **)malloc((sizeof(char *)) * (ft_arr_len(paths) + 1));
	// if (!paths)
	// 	mallocerr
	x = 0;
	while (paths[x])
	{
		tmp = ft_strjoin(paths[x], "/");
		// if (!tmp)
		// 	"malloc error"
		res[x] = tmp;
		x++;
	}
	res[x] = NULL;
	return (res);
}

/*
* look for the envp:path where the cmd belong  before execve (1/2)
*/
char	*find_path_cmd(t_data *data, int i)
{
	char	**tmp;
	char	*cmd;
	int 	x;

	tmp = prepare_paths(search_env(data, "PATH"));
	// if (!tmp)
	// 	errormalloc
	x = 0;
	while (tmp[x])
	{
		cmd = ft_strjoin(tmp[x], data->token[i].cmd[0]);
		// if (!cmd)
		// 	"error malloc"
		if (access(cmd, 0) == 0)
		{
			ft_free_arr(tmp);
			return (cmd);
		}
		free(cmd);
		x++;
	}
	return (NULL);
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

/* TEST EXECUTE*/ //delete later
void	execute(t_data	*data)
{
	if (data->cmd_count == 1 && is_builtin(data) == TRUE)
		exec_builtin(data);
	else
	{
		create_pipes(data);
		create_forks(data);
		close_pipes(data);
		int x;
		x = 0;
		if (data->cmd_count > 1)
		{
			while(x < data->pipe_count)
			{
				printf("pipe index: %d\n", x);
				close(data->pipe[x][0]);
				close(data->pipe[x][1]);
				x++;
			}
		}
		x = 0;
		while (x < data->cmd_count)
		{
			waitpid(data->pid[x], &data->status, 0);
			x++;
		}
		dprintf(2, "after WAIT\n");
	}
	return ;
}
/* we can use this one if we want improve user experience*/

// static void	line_history(char *line)
// {
// 	static char	*last = NULL;

// 	if (*line && (!last || ft_strcmp(last, line)))
// 	{
// 		add_history(line);
// 		free(last);
// 		last = ft_strdup(line);
// 	}
// }

void	signal_d()
{
	if (isatty(0))
		write (2, "exit", 5);
	exit (0);
}
/* TEST MINISHELL */ //delete later
void	ft_minishell(t_data *data)
{
	char	*line;
	int		status;

	signal_setup(SIG_PARENT);
	while (1)
	{
		status = 1;
		line = readline("\033[0;31mminishell-8.8$ \033[0m");
		if (!line)
			signal_d();
		if (line)
		{
			add_history(line);
			status = prompt_check(line);
			if (status)
				status = parse_start(data, line);
			// if (status)
			// 	execute(data);
			if (status == 0)
				printf("you have triggered my trap card!\n");
		}
		else
			free(line);
	}
	free(line);
}

int main(int ac, char **ag, char **envp)
{
	t_data	data;

	(void)ac;
	(void)ag;
	data = (t_data){0};
	if (ac != 1) // probably don't need
		return (0);
	env_setup(&data, envp);
	ft_minishell(&data);
	//int i;
	//int x;
	//i = 0;
	//while (&data.token[i])
	//{
	//	x = 0;
	//	while (&data.token[i].redir[x])
	//		printf("redir: %s", data.token[i].redir[x++]);
	//	i++;
	//}
	// start the program
	// free all the shit
	//ft_free_token(&data);
	return (0);
}
