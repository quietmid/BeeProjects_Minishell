/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:16:30 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/06 21:38:57 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envsize(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*
*  iterate thru ll and look for node
*/
t_env	*search_env(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	if (env->next != NULL)
	{
		while (env)
		{
			if (ft_strcmp(env->name, str) == 0)
				return (env);
			env = env->next;
		}
		return (NULL); // env exist but node doesnt
	}
	return (NULL); // env does not exist?
}

/*
*  create a linked list node (splitting the env name and content)
*/
t_env	*create_envnode(char *envp)
{
	t_env	*node;
	char	**tmp;

	tmp = ft_split(envp, '=');
	// if (!tmp)
	// 	"malloc fail"
	node = (void *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->name = tmp[0];
	node->content = tmp[1];
	node->next = NULL;
	return (node);
}


// /*
// * make a array of strings from envp;paths
// */
// void    get_paths(t_data *data)
// {
// 	char	**paths;
// 	paths = ft_split(, ':');
// 	//paths = ft_split(find_in_envp(envp, "PATH"), ':');
// 	// if (!paths)
// 	// 	"malloc error"
// 	data->paths = paths;
// }

/*
* malloc a copy of the envp
*/
// void	copy_envp(t_data *data, char **envp)
// {
// 	char	**res;

// 	res = ft_arr_copy(envp);
// 	// if (!res)
// 	// 	"malloc error"
// 	data->envi = res;
// }

// /*
// * temp fxn to print LL; delete later
// */
// void	printlink(t_data *data)
// {

// 	if (data->env->next != NULL)
// 	{
// 		while (data->env)
// 		{
// 			// printf("%s", data->env->name);
// 			// printf("=");
// 			// printf("%s\n", data->env->content);
// 			data->env = data->env->next;
// 		}
// 	}
// }

void	env_setup(t_data *data, char **envp)
{
	t_env	*tmp;
	t_env	*head;
	t_env	*tail;
	int		x;

	tmp = NULL;
	x = 0;
	while (envp[x])
	{
		head = create_envnode(envp[x]);
		if (tmp == NULL)
			tmp = head;
		else
		{
			tail = tmp;
			while (tail->next != NULL)
				tail = tail->next;
			tail->next = head;
		}
		x++;
	}
	data->env = tmp;
}
