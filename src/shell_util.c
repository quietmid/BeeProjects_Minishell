/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:15 by jlu               #+#    #+#             */
/*   Updated: 2024/06/04 15:45:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//error handling functions


// char	*find_cmd(char **ag, char **path)
// {
// 	char	*cmd;

// 	cmd = NULL;
// 	// if (ag[0] == NULL)
// 	// 	error_msg(ERR_CMD, ag[0]);
// 	if (ag[0][0] == '/' || ag[0][0] == '.')
// 		cmd = ag[0];
// 	else
// 		cmd = exe_cmd(ag[0], path);
// 	return (cmd);
// }

char	*find_in_envp(char **envp, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	// if (!envp || !*envp)
	// 	*envp = "PATH=/bin:/usr/bin"; ???
	i = 0;
	while (ft_strncmp(*envp, str, len))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + (len + 1));
}

/*
* make a array of strings from envp;paths
*/
char	**get_paths(char **envp)
{
	char	**paths;

	// if (!envp || !envp[0])
	// 	return (1); //exit error?
	paths = ft_split(find_in_envp(envp, "PATH"), ':');
	// if (!paths)
	// 	"malloc error"
	return (paths);
}

/*
* get the pwd from the env
*/
char	*get_pwd(char **envp)
{
	char	*pwd;

	if (!envp || !*envp) // maybe need to recheck if necessary
		pwd = getcwd(NULL, 0);
		// if (!pwd)
		// 	error
	else
		pwd = find_in_envp(envp, "PWD");
		// if (!paths)
		// 	"malloc error"
	return (pwd);
}