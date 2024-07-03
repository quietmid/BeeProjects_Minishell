/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/03 19:10:25 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* iterate thru the env ll and return key(str)node
*/
t_env	*search_env(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	if (tmp->next != NULL)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, str) == 0)
			{
				return (tmp);
			}
			tmp = tmp->next;
		}
		return (NULL); // env exist but node doesnt?
	}
	return (NULL); // env does not exist?
}

/*
* update env after cd
*/
void	update_env(t_data *data)
{
	t_env	*node;

	node = search_env(data, "OLDPWD");
	if (node)
		node->value = data->oldpwd;
	node = search_env(data, "PWD");
	if (node)
		node->value = data->pwd;
}

/*
* update the env data in the main struct after cd
*/
void	update_data(t_data *data)
{
	// if (data->oldpwd)
	// 	free(data->pwd);
	data->oldpwd = ft_strdup(data->pwd);
	if (!data->pwd)
		error(data, XMALLOC, EXIT_FAILURE);

	// if (data->oldpwd)
	// 	free(data->oldpwd);
	// if (data->pwd)
	// {
	// 	data->oldpwd = ft_strdup(data->pwd);
	// 	// if (!data->oldpwd)
	// 	// 	errormalloc
	// } 
	// if (data->pwd)
	// 	free(data->pwd);
	// if (data->pwd)
	// 	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		error(data, XMALLOC, EXIT_FAILURE);
}

/*
* execute cd "dir"
*/
char	*check_address(t_data *data, char *add)
{
	char	*res;
	t_env	*tmp;

	res = NULL;
	tmp = search_env(data, add);
	if (tmp != NULL)
	{
		res = tmp->value;
	}
	else if (tmp == NULL)
	{
		if (strcmp(add,"HOME") == 0)
			error_var(data, XCDHOME, NULL, EXIT_FAILURE);
		if (strcmp(add,"OLDPWD") == 0)
			error_var(data, XCDOLDPWD, NULL, EXIT_FAILURE);
	}
	return (res);
}

/*
* execute builtin command cd
*/
void	run_cd(t_data *data)
{
	char	*add;
	int		dash;

	dash = 0;
	if (!data->token->cmd[1] || data->token->cmd[1][0] == '~')
	{
		add = check_address(data, "HOME");
	}
	else if (data->token->cmd[1][0] == '-')
	{
		dash = 1;
		add = check_address(data, "OLDPWD");
	}
	else if (data->token->cmd[1][0] == '/')
		add = data->token->cmd[1];
	else
		add = ft_strjoin("./", data->token->cmd[1]);
	if (chdir(add) == 0)
	{
		update_data(data);
		update_env(data);
		if (dash == 1)
			ft_putendl_fd(add, 1);
	}
	else
		error_var(data, XCD, data->token->cmd[1], EXIT_FAILURE);
}
