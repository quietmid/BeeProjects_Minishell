/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:32:36 by jlu               #+#    #+#             */
/*   Updated: 2024/06/05 22:49:31 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((str[i] == ' ') && (count % 2 == 0))
			str[i] = 31;
		if (str[i] == c)
		{
			count += 1;
			//str[i] = 31;
		}
		if ((str[i] == 39 || str[i] == 34) && count == 0)
		{
			c = str[i];
			count += 1;
			//str[i] = 31;
		}
		i++;
	}
}

int	pipe_scans(char *line)
{
	int	i;
	int q_count;
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
		if ((*line == 39 || *line == 34) && q_count == 0)
		{
			c = *line;
			q_count += 1;
		}
		line++;
	}
	return (i);
}
