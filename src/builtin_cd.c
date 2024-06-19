/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/19 18:55:31 by pbumidan         ###   ########.fr       */
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
		printf("errormallod"); //error

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
		printf("error"); // error malloc
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
	if (!tmp)
	{
		if (ft_strcmp(add, "HOME") == 0)
			res = "~";
		else if (ft_strcmp(add, "OLDPWD") == 0)
			res = "-";
	}
	else
		res = tmp->value;
	return (res);
}

/*
* execute builtin command cd
*/
void	run_cd(t_data *data)
{
	char	*add;

	if (!data->token->cmd[1] || data->token->cmd[1][0] == '~')
		add = check_address(data, "HOME");
	else if (data->token->cmd[1][0] == '-')
		add = check_address(data, "OLDPWD");
	else if (data->token->cmd[1][0] == '/')
		add = data->token->cmd[1];
	else
		add = ft_strjoin("./", data->token->cmd[1]);
	if (chdir(add) == 0)
	{
		update_data(data);
		update_env(data);
	}
	else
		perror(""); // error
}
