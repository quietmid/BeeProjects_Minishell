/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:20 by jlu               #+#    #+#             */
/*   Updated: 2024/07/25 15:36:51 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_unset(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
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
		free_unset(tmp);
		x++;
	}
	data->status = 0;
}
