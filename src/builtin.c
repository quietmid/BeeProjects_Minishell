/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:01:32 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 15:42:12 by jlu              ###   ########.fr       */
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
			if (node->flag == 1)
			{
				ft_putstr_fd(node->key, 1);
				ft_putendl_fd("=\"\"", 1);
			}
			else
				ft_putendl_fd(node->key, 1);
		}
		node = node->next;
	}
}

void	run_pwd(t_data *data)
{
	ft_putendl_fd(data->pwd, 1);
	data->status = 0;
}

int	checkfirst(t_data *data, int x)
{
	if (ft_isalpha(data->token[0].cmd[x][0]) == 1)
		return (1);
	else if (data->token[0].cmd[x][0] == '_')
		return (1);
	else
		return (0);
}

int	prep_for_spit(t_data *data, int x)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (data->token[0].cmd[x][i])
	{
		if (data->token[0].cmd[x][i] == '=')
		{
			data->token[0].cmd[x][i] = 31;
			if (data->token[0].cmd[x][i + 1] == '\0')
				c = 1;
			break ;
		}
		i++;
	}
	return (c);
}
