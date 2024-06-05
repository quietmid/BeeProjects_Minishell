/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/05 15:16:58 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* look for the envp:path where the cmd belong 
*/
char	*find_path_cmd(t_data *data)
{
	char	*path_slash;
	char	*res;
	int		x;

	x = 0;
	while (data->paths[x])
	{
		path_slash = ft_strjoin(data->paths[x], "/");
		{
			// if (!path_slash)
			// 	"error malloc"
			res = ft_strjoin(path_slash, data->line[0]);
			// if (!path_slash_cmd)
			// 	"error malloc"
			free(path_slash);
		}
		if (access(res, 0) == 0)
			return (res);
		free(res);
		x++;
	}
	return (NULL);
}

void	exec_fork(t_data *data)
{
	pid_t pid = fork();
	char	*path_cmd;

	if (pid == -1)
        printf("fork");
	//printf("%s", *line);
	path_cmd = find_path_cmd(data);
	// if (!p_c);
	// 	"error command not found"
	printf("%s\n", path_cmd);
	if (pid == 0)
	{
		printf("in child");
		if (execve(path_cmd, data->line, data->envp) == -1)
			printf("fail\n");
	}
	else
		wait(NULL);
	printf("done\n");
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
	ft_minishell(&data);
	// start the program
	// free all the shit
	return (0);
}
