/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/19 21:24:28 by pbumidan         ###   ########.fr       */
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
		cmd = ft_strjoin(tmp[x], data->token->cmd[0]);
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


/* TEST EXECUTE*/ //delete later
void	execute(t_data	*data)
{
	if (data->cmd_count == 1 && is_builtin(data) == TRUE)
		exec_builtin(data);
	else
	{
		create_pipes(data);
		create_forks(data);
	}
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
		line = readline("minishell-8.8$ ");
		if (!line)
			signal_d();
		add_history(line);
		if (!quotes_check(line))
			status = 0;
		if (status)
			status = parse_start(data, line);
		if (status)
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
	ft_free_token(&data);
	return (0);
}
