/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:15 by jlu               #+#    #+#             */
/*   Updated: 2024/06/03 16:29:08 by jlu              ###   ########.fr       */
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

char	*find_path(char **envp)
{
	int	i;

	if (!envp || !*envp)
		*envp = "PATH=/bin:/usr/bin";
	i = 0;
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + 5);
}

/*
* make a array of strings from envp;paths
*/
char	**get_paths(char **envp)
{
	char	**paths;

	// if (!envp || !envp[0])
	// 	return (1); //exit error?
	paths = ft_split(find_path(envp), ':');
	// if (!paths)
	// 	"malloc error"
	return (paths);
}
