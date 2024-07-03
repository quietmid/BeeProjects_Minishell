/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:01:32 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/03 22:56:24 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* execute builtin env
*/
void	run_env(t_data *data)
{
	t_env	*env;

	if (!data->token->cmd[1])
	{
		env = data->env;
		if (data->env->next != NULL)
		{
			while (env)
			{
				if (env->value)
				{
					ft_putstr_fd(env->key, 1);
					ft_putstr_fd("=", 1);
					ft_putstr_fd(env->value, 1);
					ft_putstr_fd("\n", 1);
				}
				env = env->next;
			}
		}
		// error? can env be NULL?
	}
// 	else
// 		"error invalid flag"
}

/*
* execute builtin pwd
*/
void	run_pwd(t_data *data)
{
	//t_env	*node;
	char	*pwd;

	if (!data->token->cmd[1])
	{
		// node = search_env(data, "PWD");
		// if (node)
		// {
		// 	if (node->value)
		// 		ft_putstr_fd(node->value, 2);
		// 		ft_putstr_fd("\n", 2);
		// 	else
		// 	{
		// 		pwd = getcwd(NULL, 0);
		// 		// if (!pwd)
		// 		// 	"getcwd fail"
		// 		ft_putendl_fd(pwd, 2);
		// 	}
		// }
		// else
		// {
			pwd = getcwd(NULL, 0);
			// if (!pwd)
			// 	"getcwd fail"
			ft_putendl_fd(pwd, 1);
			data->pwd = pwd;
	// 	}
	// }
// 	else
// 		"error invalid flag"
	}
}

void	run_export3(t_data *data)
{
	t_env	*node;
	
	node = data->env;
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		if (node->value)
		{
			ft_putstr_fd(node->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(node->value, 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putendl_fd(node->key, 1);	
		}
		node = node->next;
	}
}
/*
* execute builtin export (2/2)
*/
void	run_export2(t_data *data)
{
	t_env	*node;
	t_env	*new;

	node = data->env;
	new = create_envnode(data->token->cmd[1]);
	if (node == NULL)
		node = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

/*
* execute builtin export (1/2)
*/
void	run_export(t_data *data)
{
	t_env	*node;
	char	**str;
	int 	x;
	
	x = 1;
	if (ft_arr_len(data->token->cmd) == 1)
		run_export3(data);
	else
	{
		while (data->token->cmd[x])
		{
			printf("x : %s\n", data->token->cmd[x]);
			str = ft_split(data->token[0].cmd[x], '=');
				// if (!str)
				// 	"error malloc"
			node = search_env(data, str[0]);
			// if (node && ft_arr_len(str) == 1)
			// 	node->value = NULL;
			if (node && ft_arr_len(str) == 2)
				node->value = str[1];
			else
			{
				run_export2(data);
			}
			x++;
		}
	}
}

/*
* execute builtin unset,
*/
void	run_unset(t_data *data)
{
	t_env	*tmp;
	t_env	*prev;

	if (ft_arr_len(data->token->cmd) == 2)
	{
		tmp = data->env;
		prev = NULL;
		while (tmp && ft_strcmp(tmp->key, data->token->cmd[1]) != 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
			return ;
		if (prev == NULL)
			data->env = tmp->next;
		else
			prev->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free (tmp);
	}
// 	else
// 		"error invalid flag"
}
