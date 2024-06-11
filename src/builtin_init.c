/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:50:33 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/11 19:21:13 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
* execute builtin pwd
*/
void	run_pwd(t_data *data)
{
	t_env	*node;
	char	*pwd;

	if (!data->line[1])
	{
		node = search_env(data, "PWD");
		if (node)
		{
			ft_putstr_fd(node->value, 2);
			ft_putstr_fd("\n", 2);
		}
		else
		{
			pwd = getcwd(NULL, 0);
			// if (!pwd)
			// 	"getcwd fail"
			ft_putendl_fd(pwd, 2);
		}
	}
// 	else
// 		"error invalid flag"
}

/*
* execute builtin env
*/
void	run_env(t_data *data)
{
	t_env	*env;

	if (!data->line[1])
	{
		env = data->env;
		if (data->env->next != NULL)
		{
			while (env)
			{
				ft_putstr_fd(env->key, 2);
				ft_putstr_fd("=", 2);
				ft_putstr_fd(env->value, 2);
				ft_putstr_fd("\n", 2);
				env = env->next;
			}
		}
		// error? can env be NULL?
	}
// 	else
// 		"error invalid flag"
}

/*
* check first string in input if builtin, return 1 if true 0 if false
*/
int	is_builtin(t_data *data)
{
	if (data->line[0] == NULL)
		return (FALSE);
	else if (ft_strcmp(data->line[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(data->line[0], "exit") == 0)
		return (TRUE);
	else
		return (FALSE);
}
/*
* execute builtin commands
*/
void	exec_builtin(t_data *data)
{
	// if (ft_strcmp(data->line[0], "echo") == 0)
	// 	run_echo(data);
	if (ft_strcmp(data->line[0], "cd") == 0)
		run_cd(data);
	else if (ft_strcmp(data->line[0], "pwd") == 0)
		run_pwd(data);
	// else if (ft_strcmp(data->line[0], "export") == 0)
	// else if (ft_strcmp(data->line[0], "unset") == 0)
	else if (ft_strcmp(data->line[0], "env") == 0)
		run_env(data);
	else if (ft_strcmp(data->line[0], "exit") == 0)
		exit(0);
}

