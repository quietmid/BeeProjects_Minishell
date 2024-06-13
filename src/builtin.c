/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:01:32 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/13 16:31:55 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				if (env->value)
				{
					ft_putstr_fd(env->value, 2);
				}
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
* execute builtin pwd
*/
void	run_pwd(t_data *data)
{
	//t_env	*node;
	char	*pwd;

	if (!data->line[1])
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
			ft_putendl_fd(pwd, 2);
	// 	}
	// }
// 	else
// 		"error invalid flag"
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
	new = create_envnode(data->line[1]);
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

	// if (ft_arr_len(data->line) > 2)
	// {
	// 	"error"
	// }
	if (ft_strchr(data->line[1], '='))
	{
		str = ft_split(data->line[1], '=');
		// if (!str)
		// 	"error malloc"
		node = search_env(data, str[0]);
		if (node && ft_arr_len(str) == 1)
			node->value = ft_strdup("");
		else if (node && ft_arr_len(str) == 2)
			node->value = str[1];
		else
			run_export2(data);
	}
}

void	del_node(t_data *data, t_env *node)
{
	(void)data; // until error handling done
	free(node->key);
	if (node->value)
		free(node->value);
}

// /*
// * iterate thru the env ll and return key(str)node
// */
// t_env	*search_env(t_data *data, t_env *node)
// {
// 	t_env	*tmp;

// 	tmp = data->env;
// 	if (tmp->next != NULL)
// 	{
// 		while (tmp)
// 		{
// 			if (ft_strcmp(tmp->next, node) == 0)
// 			{
// 				return (tmp);
// 			}
// 			tmp = tmp->next;
// 		}
// 		return (NULL); // env exist but node doesnt?
// 	}
// 	return (NULL); // env does not exist?
// }

/*
* execute builtin wxport
*/
void	run_unset(t_data *data)
{
	t_env	*head;
	//t_env	*next;
	t_env	*tmp;

	if (ft_arr_len(data->line) == 2)
	{
		printf("%s", data->line[1]);
		tmp = search_env(data, data->line[1]);
		head = data->env;
		while(head)
		{
			if (head->next->key == tmp->key)
				printf("found!\n");
		}
		// next = index->next;
		// del_node(data, index);
		// free(index);
		// tmp = data->env;
		// while (tmp->next)
		// 	tmp = tmp->next;
		// tmp = next;
		// else //maybe not needed if we can defend
		// {
		// 	node = data->env;
		// 	new = create_envnode(data->line[1]);
		// 	if (node == NULL)
		// 		node = new;
		// 	else
		// 	{
		// 		while (node->next != NULL)
		// 			node = node->next;
		// 		node->next = new;
		// 	}
		// }
	}
// 	else
// 		"error invalid flag"
}

