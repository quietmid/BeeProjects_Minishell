/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/18 22:33:18 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_data(t_data *data)
{
	char	*tmp;

	free(data->pwd);
	data->oldpwd = data->pwd;
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		error(data, XCWD, EXIT_FAILURE);
	}
	data->pwd = tmp;
}

static int	run_cd2(t_data *data, char *str, char **add)
{
	t_env	*tmpenv;

	tmpenv = search_env(data, str);
	if (tmpenv != NULL)
	{
		*add = ft_strdup(tmpenv->value);
		if (!*add)
			error(data, XMALLOC, EXIT_FAILURE);
	}
	else if (tmpenv == NULL)
	{
		if (strcmp(str, "HOME") == 0)
		{
			error_cd(data, XCDHOME, NULL, 0);
			return (FALSE);
		}
		else if (strcmp(str, "OLDPWD") == 0)
		{
			error_cd(data, XCDOLDPWD, NULL, 0);
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	run_cd3(t_data *data, char **add)
{
	char	*tmp;

	if (data->token->cmd[1][0] == '/')
	{
		*add = ft_strdup(data->token->cmd[1]);
		if (!add)
			error(data, XMALLOC, EXIT_FAILURE);
	}
	else
	{
		tmp = ft_strdup(data->token->cmd[1]);
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		*add = ft_strjoin("./", tmp);
		free(tmp);
	}
}

static void	run_chdir(t_data *data, char *add, int dash)
{
	if (chdir(add) == 0)
	{
		update_data(data);
		update_env(data);
		if (dash == 1)
			ft_putendl_fd(add, 1);
		free(add);
	}
	else
	{
		error_cd(data, XCD, data->token->cmd[1], 0);
	}
}

void	run_cd(t_data *data)
{
	char	*add;
	int		dash;

	dash = 0;
	if (!data->token->cmd[1]
		|| (data->token->cmd[1][0] == '~' && !data->token->cmd[2]))
	{
		if (run_cd2(data, "HOME", &add) == FALSE)
			return ;
	}
	else if (data->token->cmd[1][0] == '-' && !data->token->cmd[2])
	{
		dash = 1;
		if (run_cd2(data, "OLDPWD", &add) == FALSE)
			return ;
	}
	else
	{
		run_cd3(data, &add);
	}
	run_chdir(data, add, dash);
}
