/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/05 22:52:39 by jlu              ###   ########.fr       */
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
		signal_setup(SIG_CHILD);
		printf("in child");
		if (execve(path_cmd, data->line, data->envp) == -1)
			printf("fail\n");
	}
	else
		wait(NULL);
	printf("done\n");
}

//void	parse(t_data *data, const char *line)
//{
//	data->line = ft_split(line, ' ');
//	// if (!data->line)
//	// {
//	// 		"malloc error"? // what if we input NULL?
//	// }
//}

void	execute(t_data	*data)
{
	if (is_builtin(data) == 1)
		exec_builtin(data);
	else
		exec_fork(data);
}
void	ft_minishell(t_data *data)
{
	char *line;

	//(void)data;
	while (1)
	{
		signal_setup(SIG_PARENT);
		line = readline("minishell-8.8$ ");
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			line = "exit";
		}
		if (!parse_start(data, line))
			break ;
		//execute(data);
		free(line);
	}
	free(line);
}


int main(int ac, char **ag, char **envp)
{
	t_data	data;
	
	data = (t_data){0};
	(void)ac;
	(void)ag;
	data.envp = envp;
	data.paths = get_paths(envp);
	//init_data(&data);
	ft_minishell(&data);
	// start the program
	// free all the shit
	return (0);
}
