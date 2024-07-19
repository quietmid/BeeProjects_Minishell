/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:08:48 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/19 18:04:24 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 34 = " , 39 = '
int	ft_isquote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

void	ft_removequotes(char *str)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (!q && ft_isquote(str[i]))
		{
			q = str[i];
			str[i] = 31;
		}
		else if (str[i] == q)
		{
			q = 0;
			str[i] = 31;
		}
		i++;
	}
}

void	ft_unquotes(t_token *t)
{
	int		i;
	size_t	x;

	i = -1;
	while (++i < t->redir_len)
	{
		if (ft_isquote(t->redir[i][0][0]))
			ft_removequotes(t->redir[i][0]);
		if (ft_isquote(t->redir[i][1][0]))
			ft_removequotes(t->redir[i][1]);
	}
	i = -1;
	while (++i < t->cmd_len && t->cmd != NULL)
	{
		x = 0;
		while (x < ft_strlen(t->cmd[i]))
		{
			if (ft_isquote(t->cmd[i][x]))
			{
				ft_removequotes(t->cmd[i]);
				break ;
			}
			x++;
		}
	}
}
