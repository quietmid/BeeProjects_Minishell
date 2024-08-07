/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:24:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 17:51:20 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(char *cmd)
{
	struct stat	filestat;

	if (stat(cmd, &filestat) == 0)
	{
		if (S_ISDIR(filestat.st_mode))
			return (TRUE);
	}
	return (FALSE);
}

static void	prepare_paths(t_data *data, t_env *env)
{
	char	**paths;

	paths = ft_split(env->value, ':');
	if (!paths)
		error(data, XMALLOC, EXIT_FAILURE);
	data->paths = paths;
}

static char	*find_path_cmd(t_data *data, int i)
{
	char	*path_slash;
	char	*path_slash_cmd;
	int		x;

	prepare_paths(data, search_env(data, "PATH"));
	x = 0;
	while (data->paths[x])
	{
		path_slash = ft_strjoin(data->paths[x], "/");
		{
			if (!path_slash)
				error(data, XMALLOC, EXIT_FAILURE);
			path_slash_cmd = ft_strjoin(path_slash, data->token[i].cmd[0]);
			if (!path_slash_cmd)
				error(data, XMALLOC, EXIT_FAILURE);
			free(path_slash);
		}
		if (access(path_slash_cmd, 0) == 0)
			return (path_slash_cmd);
		free(path_slash_cmd);
		x++;
	}
	return (NULL);
}

static void	check_path(t_data *data, int x, char **path)
{
	if (data-> token[x].cmd)
	{
		if (is_builtin_x(data, x) == TRUE)
		{
			exec_builtin(data, x);
			exit(data->status);
		}
		else if (is_builtin_x(data, x) == 2)
		{
			*path = ft_strjoin("/usr/bin/", data->token[x].cmd[0]);
			if (!*path)
				error(data, XMALLOC, EXIT_FAILURE);
		}
		else if (search_env(data, "PATH"))
		{
			*path = find_path_cmd(data, x);
			if (!*path)
				error_var(data, XCMD, data->token[x].cmd[0], 127);
		}
		else
			error_var(data, XNOFILE, data->token[x].cmd[0], 127);
	}
}

void	child_process(t_data *data, int x)
{
	char	*path;

	if (data->cmd_count > 1 || data->token[x].redir)
		redirect(data, x);
	if ((data-> token[x].cmd && data->token[x].cmd[0][0] == '.')
		|| (data-> token[x].cmd && data->token[x].cmd[0][0] == '/'))
	{
		if (is_directory(data->token[x].cmd[0]) == TRUE)
			error_var(data, XDIR, data->token[x].cmd[0], 126);
		if (access(data->token[x].cmd[0], X_OK) != 0)
			error_var(data, XPERM, data->token[x].cmd[0], 127);
		path = data->token[x].cmd[0];
	}
	else
		check_path(data, x, &path);
	if (data->token[x].cmd && data->ms_stat == 0)
	{
		env_to_arr(data);
		if (execve(path, data->token[x].cmd, data->env_arr) < 0)
			error(data, XEXEC, EXIT_FAILURE);
	}
	else
		exit(data->status);
}
