/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/12 18:43:30 by pbumidan         ###   ########.fr       */
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

/* TEST FORKING */ //delete later
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
				printf("mallocerror "); // fix error
			env_to_arr(data);
			execve(data->path_cmd, data->line, data->env_arr);
			// remember to check if execve fails to free all mallocs otherwise its fine.
		}
		printf(" error *"); // fix error
	}
	wait (NULL);
}

/* TEST PARSE */ //delete later
void	parse(t_data *data, const char *line)
{
	data->line = ft_split(line, ' ');
}

/* TEST EXECUTE*/ //delete later
void	execute(t_data	*data)
{
	if (is_builtin(data) == TRUE)
		exec_builtin(data);
	else
		exec_fork(data);
}

/* TEST MINISHELL */ //delete later
void	ft_minishell(t_data *data)
{
	char	*line;

	while (1)
	{
		signal_setup(SIG_PARENT);
		line = readline("minishell-8.8$ ");
		parse(data, line);
		execute(data);
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
	// start the program
	// free all the shit
	return (0);
}

// void	ft_minishell(t_data *data)
// {
// 	char *line;
// 	char *end;

// 	//(void)data;
// 	end = "exit";
// 	while (1)
// 	{
// 		signal_setup(SIG_PARENT);
// 		line = readline("minishell-8.8$ ");
// 		if (ft_strcmp(line, end) == 0)
// 			break ;
// 		if (!parse_start(data, line))
// 			break ;
// 		//execute(data);
// 		free(line);
// 		//line = readline("minishell-8.8$ ");
// 	}
// 	free(line);
// 	//unlink(".temp"); // unlink temp when all finished
// }