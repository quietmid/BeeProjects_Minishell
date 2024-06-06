/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/06 23:02:06 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**prepare_paths(t_env *env)
{
	char	**paths;
	char	**res;
	char	*tmp;
	int		x;

	paths = ft_split(env->content, ':');
	// if (!paths)
	// 	mallocerr
	//ft_arr_print(paths);
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
	return(res);
}

/*
* look for the envp:path where the cmd belong 
*/
char	*find_path_cmd(t_data *data)
{
	char	**tmp;
	char	*cmd;
	int		x;

	tmp = prepare_paths(search_env(data, "PATH"));
	// if (!tmp)
	// 	errormalloc
	x = 0;
	while (tmp[x])
	{
		cmd = ft_strjoin(tmp[x], data->line[0]);
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

void	exec_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("forkerror"); //error
	if (pid == 0)
	{
		if (search_env(data, "PATH"))
		{
			data->path_cmd = find_path_cmd(data);
			if (!data->path_cmd)
				printf("mallocerror"); // error
			env_to_arr(data);
			execve(data->path_cmd, data->line, data->envi);
		}
		printf("environ error"); // error
	}
}

void	parse(t_data *data, const char *line)
{
	data->line = ft_split(line, ' ');
	// if (!data->line)
	// {
	// 		"malloc error"? // what if we input NULL?
	// }
}

void	execute(t_data	*data)
{
	if (is_builtin(data) == TRUE)
		exec_builtin(data);
	else
		exec_fork(data);
}

void	ft_minishell(t_data *data)
{
	//int file;
	char *line;
	// char *end;

	// file = open(".temp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// if (file < 0) // 
	// 	exit(EXIT_FAILURE);
	// line = readline("minishell-8.8$ ");
	// end = "exit";
	//while (ft_strcmp(line, end) != 0) // later on, we will switch to just while (1)? because typing exit will be a command
	while (1)
	{
		//ft_putstr_fd(line, file);
		// if (parse the line == cmd)
		// 		execute the cmd
		// else
		// 		minishell-8.8$: "line": command not found
		line = readline("minishell-8.8$ ");
		parse(data, line);
		execute(data);
		free(line);
		//line = readline("minishell-8.8$ ");
	}
	free(line);
	//unlink(".temp"); // unlink temp when all finished
}

int main(int ac, char **ag, char **envp)
{
	t_data	data;
	
	data = (t_data){0};
	ag = NULL;
	if (ac != 1) // probably don't need
		return (0);
	signal_setup();
	env_setup(&data, envp);
	//printlink(&data);
	//env_to_arr(&data);
	//ft_arr_print(data.envi);
	ft_minishell(&data);
	// start the program
	// free all the shit
	return (0);
}
