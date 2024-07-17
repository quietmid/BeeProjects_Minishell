/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:25 by jlu               #+#    #+#             */
/*   Updated: 2024/07/17 14:46:22 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		extract_cmd(char **temp, int i)
{
	if ((ft_isredir(temp[i][1]) && !temp[i][2]) || !temp[i][1])
	{
		i++;
		if (temp[i])
			i++;
	}
	else if (!ft_isredir(temp[i][ft_strlen(temp[i])]))
		i += 1;
	return (i);
}

int	extract_redir(char *str, char **redir, int i)
{
	if (str[i + 1] == str[i])
	{			
		redir[0] = ft_safe_substr(str, i, 2);
		i += 2;			
	}
	else
	{
		redir[0] = ft_safe_substr(str, i, 1);
		i++;
	}
	return (i);
}

char **prompt_prep(char *line, int opt)
{
	char	**result;

	if (opt == 1)
		pipe_replace(line);
	else
		space_replace(line);
	result = ft_split(line, 31);
	if (!result) // err msg?
		error_msg("prompt split failed");
	return (result);
}
