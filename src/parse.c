/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/04 18:35:08 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
int empty_line(char *input)
{
	while (ft_isspace(*input))
		input++;
	if (!*input)
		return (1);
	return (0);
}

int	parse_start(t_data *data, const char *line)
{
	if (!line || !*line || empty_line(line))
		return (0); // failure
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		// once the first white space is passed 
		// we look for the first part of the cmd/argv and store it and update it and then we jump to the next one
	}
	return (1);
}

void	parse(t_data *data, const char *line)
{
	data->line = ft_split(line, ' ');
	// if (!data->line)
	// {
	// 		"malloc error"? // what if we input NULL?
	// }
}
/*
* execute the cmd, returns 0 on success and -1 when it fails
*/
int execute_cmd()
{
	return (0);
}
