/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:01:32 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/17 22:42:05 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_export_only(t_data *data)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		if (node->value[0] != '\0')
		{
			ft_putstr_fd(node->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(node->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
		{
			ft_putendl_fd(node->key, 1);
		}
		node = node->next;
	}
}

void	run_pwd(t_data *data)
{
	ft_putendl_fd(data->pwd, 1);
}

void	run_unset(t_data *data)
{
	t_env	*tmp;
	t_env	*prev;
	int		x;

	x = 1;
	while (x < ft_arr_len(data->token->cmd))
	{
		tmp = data->env;
		prev = NULL;
		while (tmp && ft_strcmp(tmp->key, data->token->cmd[x]) != 0)
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
		free(tmp);
		x++;
	}
}
