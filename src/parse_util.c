/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:32:36 by jlu               #+#    #+#             */
/*   Updated: 2024/06/24 18:52:24 by jlu              ###   ########.fr       */
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
	int q_count; //quote count
	char c;

	i = 0;
	q_count = 0;
	while (*line)
	{
		if (q_count == 2)
			q_count = 0;
		if (*line == 124 && (q_count % 2 == 0))
			i++;
		if (*line == c)
			q_count += 1;
		if (ft_isquote(*line) && q_count == 0)
		{
			c = *line;
			q_count += 1;
		}
		line++;
	}
	i += 1;
	return (i);
}

int	quotes_check(char *line)
{
	char q;

	q = 0;
	while (*line)
	{
		if (!q && ft_isquote(*line))
			q = *line;
		else if (*line == q)
			q = 0;
		line++;
	}
	if (q == 0)
		return (1);
	print_errors(ERR_QUOTES);
	return (0);
}