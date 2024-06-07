/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:16:30 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/07 21:45:29 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* calculate the size of the env ll
*/
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
* iterate thru the env ll and check if key(str)exist
*/
int	env_key_exist(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

/*
* iterate thru the env ll and return key(str)node
*/
t_env	*search_env(t_data *data, char *str)
{
	t_env	*env;

	env = data->env;
	if (env->next != NULL)
	{
		while (env)
		{
			if (ft_strcmp(env->key, str) == 0)
				return (env);
			env = env->next;
		}
		return (NULL); // env exist but node doesnt
	}
	return (NULL); // env does not exist
}

/*
*  create a linked list node (splitting the key and value with '=')
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
	node->key = tmp[0];
	node->value = tmp[1];
	node->next = NULL;
	return (node);
}

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
// 			printf("%s", data->env->name);
// 			printf("=");
// 			printf("%s\n", data->env->content);
// 			data->env = data->env->next;
// 		}
// 	}
// }

/*
* convert env ll into an array before execve
*/
void	env_to_arr(t_data *data)
{
	t_env	*env;
	char	**res;
	char	*tmp;
	int		x;

	x = 0;
	res = (char **)malloc((sizeof(char *)) * (ft_envsize(data->env) + 1));
	env = data->env;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		// if (!tmp)
		// 	malloc error
		res[x] = ft_strjoin(tmp, env->value);
		// if (!res[x])
		// 	malloc error
		free(tmp);
		x++;
		env = env->next;
	}
	res[x] = NULL;
	data->env_arr = res;
}

/* 
*export the env variables and create a linked list from it.
*/
void	env_setup(t_data *data, char **envp)
{
	t_env	*head;
	t_env	*index;
	t_env	*tail;
	int		x;

	head = NULL;
	x = 0;
	while (envp[x])
	{
		index = create_envnode(envp[x]);
		if (head == NULL)
			head = index;
		else
		{
			tail = head;
			while (tail->next != NULL)
				tail = tail->next;
			tail->next = index;
		}
		x++;
	}
	data->env = head;
}
