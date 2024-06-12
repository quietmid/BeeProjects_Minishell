/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:32:36 by jlu               #+#    #+#             */
/*   Updated: 2024/06/12 20:19:27 by jlu              ###   ########.fr       */
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
		if ((str[i] == 39 || str[i] == 34) && count == 0)
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
		if ((*line == 39 || *line == 34) && q_count == 0)
		{
			c = *line;
			q_count += 1;
		}
		line++;
	}
	i += 1;
	return (i);
}

t_token_type deter_token_type(char *input)
{
	if (input[0] == '$')
		return (DOLLAR_TOKEN);
	else if (input[0] == '|')
		return (PIPE_TOKEN);
	else if (input[0] == '<' && input[1] == '<')
		return (HERE_DOC_TOKEN);
	else if (input[0] == '>' && input[1] == '>')
		return (REDIR_APP_OUT_TOKEN);
	else if (input[0] == '<')
		return (REDIR_IN_TOKEN);
	else if (input[0] == '>')
		return (REDIR_OUT_TOKEN);
	else if (input[0] == '$')
		return (DOLLAR_TOKEN);
	else
		return (STRING_TOKEN);
	// do we need to check for input[0] == null?
}