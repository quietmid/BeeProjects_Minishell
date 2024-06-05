/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:16:30 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/05 16:15:13 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
* malloc a copy of the envp
*/
void	get_envp(t_data *data, char **envp)
{
	char	**res;

	res = ft_arr_copy(envp);
	// if (!res)
	// 	"malloc error"
	data->envp = res;
}

/*
* get the pwd from the env
*/
void    get_pwd(t_data *data, char **envp)
{
	char	*pwd;

	if (!envp || !*envp) // maybe need to recheck if necessary
		pwd = getcwd(NULL, 0);
		// if (!pwd)
		// 	error getcw fail
	else
		pwd = find_in_envp(envp, "PWD");
		// if (!paths)
		// 	"malloc error"
	data->pwd = pwd;
}

/*
* make a array of strings from envp;paths
*/
void    get_paths(t_data *data, char **envp)
{
	char	**paths;
	(void)envp;
	// if (!envp || !envp[0])
	// 	return (1); //exit error?
	paths = ft_split(getenv("PATH"), ':');
	//paths = ft_split(find_in_envp(envp, "PATH"), ':');
	// if (!paths)
	// 	"malloc error"
	data->paths = paths;
}


void	env_setup(t_data *data, char **envp)
{
	get_envp(data, envp);
	get_pwd(data, envp);
	get_paths(data, envp);
}
