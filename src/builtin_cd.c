/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/10 20:32:47 by pbumidan         ###   ########.fr       */
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
	//if (tmp->next != NULL)
	//{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, str) == 0)
			{
				return (tmp);
			}
			tmp = tmp->next;
		}
		return (NULL);
//	}
	//return (NULL);
}

/*
* update env after cd
*/
void	update_env(t_data *data)
{
	t_env	*node;
	char	*add;

	node = search_env(data, "OLDPWD");
	if (node)
	{
		add = data->oldpwd;
		node->value = add;
	}
	node = search_env(data, "PWD");
	if (node)
	{
		add = data->pwd;
		node->value = add;
	}
}

/*
* update the env data in the main struct after cd
*/
void	update_data(t_data *data)
{
	char *tmp;
	// if (data->oldpwd)
	// 	free(data->pwd);
	tmp = data->pwd;
	data->oldpwd = ft_strdup(tmp);
	if (!data->oldpwd)
		error(data, XMALLOC, EXIT_FAILURE);
	free(tmp);
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
	tmp = getcwd(NULL, 0);
	if (!tmp)
		error(data, XMALLOC, EXIT_FAILURE);
	data->pwd = tmp;
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
		res = ft_strdup(tmp->value);
		if (!res)
			error(data, XMALLOC, EXIT_FAILURE);
	}
	else if (tmp == NULL)
	{
		if (strcmp(add,"HOME") == 0)
			error_cd(data, XCDHOME, NULL);
		if (strcmp(add,"OLDPWD") == 0)
			error_cd(data, XCDOLDPWD, NULL);
	}
	return (res);
}

/*
* execute builtin command cd
*/
// void	run_cd(t_data *data)
// {
// 	char	*add;
// 	int		dash;
// 	char	*tmp;

// 	dash = 0;
// 	if (!data->token->cmd[1] || data->token->cmd[1][0] == '~')
// 	{
// 		add = check_address(data, "HOME");
// 		if (add == NULL)
// 			return ;
// 	}
// 	else if (data->token->cmd[1][0] == '-')
// 	{
// 		dash = 1;
// 		add = check_address(data, "OLDPWD");
// 		if (add == NULL)
// 			return ;
// 	}
// 	else if (data->token->cmd[1][0] == '/')
// 	{
// 		add = ft_strdup(data->token->cmd[1]);
// 		if (!add)
// 			error(data, XMALLOC, EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		tmp = ft_strdup(data->token->cmd[1]);
// 		if (!tmp)
// 			error(data, XMALLOC, EXIT_FAILURE);
// 		add = ft_strjoin("./", tmp);
// 		free(tmp);
// 	}
// 	if (chdir(add) == 0)
// 	{
// 		update_data(data);
// 		update_env(data);
// 		if (dash == 1)
// 			ft_putendl_fd(add, 1);
// 		free(add);
// 	}
// 	else
// 	{
// 		error_cd(data, XCD, data->token->cmd[1]);
// 		return ;	
// 	}
	
// }

void	run_cd(t_data *data)
{
	char	*add;
	int		dash;
	char	*tmp;
	t_env	*tmpenv;

	dash = 0;
	if (!data->token->cmd[1] || data->token->cmd[1][0] == '~')
	{
		tmpenv = search_env(data, "HOME");
		if (tmpenv != NULL)
		{
			add = ft_strdup(tmpenv->value);
			if (!add)
				error(data, XMALLOC, EXIT_FAILURE);
		}
		else if (tmpenv == NULL)
			error_cd(data, XCDHOME, NULL);
	}
	else if (data->token->cmd[1][0] == '-')
	{
		dash = 1;
		tmpenv = search_env(data, "OLDPWD");
		if (tmpenv != NULL)
		{
			add = ft_strdup(tmpenv->value);
			if (!add)
				error(data, XMALLOC, EXIT_FAILURE);
		}
		else if (tmpenv == NULL)
			error_cd(data, XCDOLDPWD, NULL);
	}
	else if (data->token->cmd[1][0] == '/')
	{
		add = ft_strdup(data->token->cmd[1]);
		if (!add)
			error(data, XMALLOC, EXIT_FAILURE);
	}
	else
	{
		tmp = ft_strdup(data->token->cmd[1]);
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		add = ft_strjoin("./", tmp);
		free(tmp);
	}
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
		error_cd(data, XCD, data->token->cmd[1]);
		return ;	
	}
}
