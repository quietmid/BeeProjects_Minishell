/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/07/11 18:57:35 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* support find_path_cmd fxn (2/2)
*/
char	**prepare_paths(t_data *data, t_env *env)
{
	char	**paths;
	char	**res;
	char	*tmp;
	char 	*str;
	int		x;

	paths = ft_split(env->value, ':');
	if (!paths)
		error(data, XMALLOC, EXIT_FAILURE);
	res = (char **)malloc((sizeof(char *)) * (ft_arr_len(paths) + 1));
	if (!res)
		error(data, XMALLOC, EXIT_FAILURE);
	x = 0;
	while (paths[x])
	{
		str = ft_strdup(paths[x]);
		if (!str)
			error(data, XMALLOC, EXIT_FAILURE);
		free(paths[x]);
		tmp = ft_strjoin(str, "/");
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
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

	tmp = prepare_paths(data, search_env(data, "PATH"));
	if (!tmp)
	 	error(data, XMALLOC, EXIT_FAILURE);
	x = 0;
	while (tmp[x])
	{
		if (data->token[i].cmd[0])
		{
			cmd = ft_strjoin(tmp[x], data->token[i].cmd[0]);
			if (!cmd)
			 	error(data, XMALLOC, EXIT_FAILURE);
			if (access(cmd, 0) == 0)
			{
				ft_free_arr(tmp);
				return (cmd);
			}
			free(cmd);
			x++;
		} 
	}
	return (NULL);
}

/* TEST EXECUTE*/ //delete later
void	execute(t_data	*data)
{
	if (data->cmd_count == 1 && is_builtin(data) == TRUE)
	{
		if (data->token[0].redir != NULL)
			redirect_builtin(data, 0);	
		exec_builtin(data);
		if (data->token[0].redir != NULL)
			restore_stdio(data, 0);
		free_single_token(data, 0);
	}
	else
	{
		create_pipes(data);
		create_forks(data);
		close_pipes(data);
		int x;
		x = 0;
		while (x < data->cmd_count)
		{
			waitpid(data->pid[x], &data->status, 0);
			x++;
		}
		dprintf(1, "status: %d\n", data->status);
		ft_free_token(data);
		ft_free_before_loop(data);
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

	while (1)
	{
		signal_setup(SIG_PARENT);
		status = 1;
		line = readline("\033[0;31mminishell-8.8$ \033[0m");
		if (!line)
			signal_d();
		if (line && *line != '\0')
		{
			add_history(line);
			status = prompt_check(data, line);
			if (status)
				status = parse_start(data, line);
			if (status)
			{
			 	execute(data);
			}
			//ft_free_before_loop(data);
		}	
		free(line);
	}
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
	free_data_all(&data, 0);
	// start the program
	// free all the shit
	//free_data_all(&data, 1);
	return (0);
}
