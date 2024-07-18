/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:41:40 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/18 22:19:37 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_envnode(t_data *data, char *envp)
{
	t_env	*node;
	char	**tmp;

	tmp = ft_split(envp, '=');
	if (!tmp)
		error(data, XMALLOC, EXIT_FAILURE);
	node = (void *)malloc(sizeof(t_env));
	{
		if (!node)
			error(data, XMALLOC, EXIT_FAILURE);
		node->key = ft_strdup(tmp[0]);
		if (!node->key)
			error(data, XMALLOC, EXIT_FAILURE);
		node->value = ft_strdup(tmp[1]);
		if (!node->value)
			error(data, XMALLOC, EXIT_FAILURE);
		node->next = NULL;
	}
	ft_free_arr(tmp);
	tmp = NULL;
	return (node);
}

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
	while (env != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		res[x] = ft_strjoin(tmp, env->value);
		if (!res[x])
			error(data, XMALLOC, EXIT_FAILURE);
		free(tmp);
		x++;
		env = env->next;
	}
	res[x] = NULL;
	data->env_arr = res;
}

static void	set_wd(t_data *data)
{
	char	*add;

	add = getcwd(NULL, 0);
	data->pwd = add;
	if (!add)
		error(data, XMALLOC, EXIT_FAILURE);
}

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
		index = create_envnode(data, envp[x]);
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
