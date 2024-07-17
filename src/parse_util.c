/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:32:36 by jlu               #+#    #+#             */
/*   Updated: 2024/07/17 16:21:05 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_replace(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (count == 2)
			count = 0;
		if ((str[i] == 124) && (count % 2 == 0))
			str[i] = 31;
		if (str[i] == c)
			count += 1;
		if (ft_isquote(str[i]) && count == 0)
		{
			c = str[i];
			count += 1;
		}
		i++;
	}
}

void	space_replace(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	c = 0;
	while (str[i])
	{
		if (count == 2)
			count = 0;
		if ((ft_isspace(str[i])) && (count % 2 == 0))
			str[i] = 31;
		if (str[i] == c)
			count += 1;
		if (ft_isquote(str[i]) && count == 0)
		{
			c = str[i];
			count += 1;
		}
		i++;
	}
}

int	pipe_scans(char *line)
{
	int	i;
	char q;

	q = 0;
	i = 0;
	while (*line)
	{
		q = quote_finder(*line, q);
		if (*line == 124 && !q)
		{
			i++;
			*line = 31;
		}
		line++;
	}
	i += 1;
	return (i);
}

int	calcu_redir(char *str)
{
	int i;
	int num_redir;
	char q;

	q = 0;
	i = 0;
	num_redir = 0;
	while (str[i])
	{
		q = quote_finder(str[i], q);
		if (ft_isredir(str[i]) && str[i + 1] == str[i] && !q)
		{
			num_redir += 1;
			i += 2;
		}
		else if (ft_isredir(str[i]) && !q)
		{
			num_redir += 1;
			i++;
		}
		else
			i++;
	}
	return (num_redir);
}

char quote_finder(char c, char q)
{
	if (!q && ft_isquote(c))
		return (c);
	else if (c == q)
		return (0);
	return (q);
}
