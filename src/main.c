/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/07 13:13:25 by jlu              ###   ########.fr       */
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
		printf("in child");
		if (execve(path_cmd, data->line, data->envp) == -1)
			printf("fail\n");
	}
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
	if (is_builtin(data) == TRUE)
		exec_builtin(data);
	else
		exec_fork(data);
}

void	ft_minishell(t_data *data)
{
	char *line;
	char *end;

	//(void)data;
	end = "exit";
	while (1)
	{
		signal_setup(SIG_PARENT);
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
	data.envp = envp;
	data.paths = get_paths(envp);
	if (ac != 1) // probably don't need
		return (0);
	signal_setup();
	ft_minishell(&data);
	// start the program
	// free all the shit
	return (0);
}
