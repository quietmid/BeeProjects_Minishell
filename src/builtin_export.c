/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:37:44 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/12 20:43:29 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_export3(t_data *data)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		if (node->value[0] != '\0')
		{
			ft_putstr_fd(node->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(node->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putendl_fd(node->key, 1);
		}
		node = node->next;
	}
}

static void	run_export2a(t_data *data, t_env **new, char **str, int x)
{
	(*new)->key = ft_strdup(str[0]);
	if (!(*new)->key)
		error(data, XMALLOC, EXIT_FAILURE);
	if (x == 2)
	{
		(*new)->value = ft_strdup(str[1]);
		if (!(*new)->value)
			error(data, XMALLOC, EXIT_FAILURE);
	}
	else if (x == 1)
	{
		(*new)->value = ft_strdup("");
		if (!(*new)->value)
			error(data, XMALLOC, EXIT_FAILURE);
	}
}

static void	run_export2(t_data *data, char **str)
{
	t_env	*node;
	t_env	*new;
	int		x;

	x = ft_arr_len(str);
	new = (void *)malloc(sizeof(t_env));
	if (!new)
		error(data, XMALLOC, EXIT_FAILURE); // something
	if (x > 2)
		error(data, XMALLOC, EXIT_FAILURE);
	else
	{
		run_export2a(data, &new, str, x);
	}
	new->next = NULL;
	node = data->env;
	if (node == NULL)
		node = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

static void	run_export4(t_data *data, char **str)
{
	t_env	*node;

	node = search_env(data, str[0]);
	if (!node)
		run_export2(data, str);
	else
	{
		if (str[1])
		{
			free(node->value);
			node->value = ft_strdup(str[1]);
			if (!node->value)
				error(data, XMALLOC, EXIT_FAILURE);
		}
	}
}

void	run_export(t_data *data)
{
	char	**str;
	int		x;

	x = 1;
	if (ft_arr_len(data->token[0].cmd) == 1)
		run_export3(data);
	else
	{
		while (x < ft_arr_len(data->token[0].cmd))
		{
			str = ft_split(data->token[0].cmd[x], '=');
			if (!str)
				error(data, XMALLOC, EXIT_FAILURE);
			run_export4(data, str);
			x++;
			ft_free_arr(str);
		}
	}
}
