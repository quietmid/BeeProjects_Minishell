/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:27:54 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/18 22:15:46 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_data *data)
{
	t_env	*env;

	if (!data->token->cmd[1])
	{
		env = data->env;
		while (env)
		{
			if (env->value[0] != '\0')
			{
				ft_putstr_fd(env->key, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd(env->value, 1);
			}
			env = env->next;
		}
	}
	else
	{
		ft_putstr_fd(data->token->cmd[1], 2);
		ft_putendl_fd(": "ERR_CMD, 2);
		data->status = 127;
	}
}

t_env	*search_env(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env(t_data *data)
{
	t_env	*node;

	node = search_env(data, "OLDPWD");
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(data->oldpwd);
	}
	node = search_env(data, "PWD");
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(data->pwd);
	}
}

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
