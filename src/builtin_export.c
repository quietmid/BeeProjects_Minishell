/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:37:44 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/20 00:03:40 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_export2a(t_data *data, t_env **new, char **str, int c)
{
	int	x;

	x =  ft_arr_len(str);
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
		(*new)->flag = 0;
		if (c == 1)
			(*new)->flag = 1;
	}
}

static void	run_export2(t_data *data, char **str, int c)
{
	t_env	*node;
	t_env	*new;

	new = (void *)malloc(sizeof(t_env));
	if (!new)
		error(data, XMALLOC, EXIT_FAILURE);
	else
	{
		run_export2a(data, &new, str, c);
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

static int	check_identifier(t_data *data, char **str)
{
	int	x;
	int	ret;

	ret = TRUE;
	if (ft_isalpha(str[0][0]) == 0 && str[0][0] != '_')
	{
		error_cd(data, XEXP, NULL, str[0][0]);
		ret = FALSE;
	}
	else
	{
		x = 1;
		while (str[0][x])
		{
			if (ft_isalnum(str[0][x]) == 0)
			{
				error_cd(data, XEXP, str[0], 0);
				ret = FALSE;
				break ;
			}
			x++;
		}
	}
	return (ret);
}

static void	run_export4(t_data *data, char **str, int c)
{
	t_env	*node;

	if (check_identifier(data, str) == FALSE)
		return ;
	node = search_env(data, str[0]);
	if (!node)
		run_export2(data, str, c);
	else
	{
		if (str[1])
		{
			free(node->value);
			node->value = ft_strdup(str[1]);
			if (!node->value)
				error(data, XMALLOC, EXIT_FAILURE);
		}
		if (c == 1)
			node->flag = 1;
	}
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
	int i;
	int c;

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

void	run_export(t_data *data)
{
	char	**str;
	int		x;
	int 	c;

	x = 1;
	if (ft_arr_len(data->token[0].cmd) == 1)
		run_export_only(data);
	else
	{
		while (x < ft_arr_len(data->token[0].cmd))
		{
			if (checkfirst(data, x) == 0)
				error_cd(data, XEXP, data->token[0].cmd[x], 0);
			else
			{
				c = prep_for_spit(data, x);
				str = ft_split(data->token[0].cmd[x], 31);
				if (!str)
					error(data, XMALLOC, EXIT_FAILURE);
				run_export4(data, str, c);
				ft_free_arr(str);
			}
			x++;
		}
	}
}
