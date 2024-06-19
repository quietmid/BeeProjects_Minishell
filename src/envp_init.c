/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:41:40 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/19 18:19:10 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
* convert env linked list into an array before execve
*/
void	env_to_arr(t_data *data)
{
	t_env	*env;
	char	**res;
	char	*tmp;
	int		x;

	tmp = NULL;
	env = data->env;
	x = 0;
	res = (char **)malloc((sizeof(char *)) * (ft_envsize(data->env) + 1));
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
*set environmental variables pwd and oldpwd from **envp for the shell for monitoring
*/
void	set_wd(t_data *data)
{
	t_env	*tmp;
	
	tmp = NULL;
	tmp = search_env(data, "PWD");
	if (tmp)
		data->pwd = ft_strdup(tmp->value);
	tmp = search_env(data, "OLDPWD");
	if (tmp)
		data->oldpwd = ft_strdup(tmp->value);
}

/* 
*Export the **envp and create a linked list from it.
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
	set_wd(data);
}
