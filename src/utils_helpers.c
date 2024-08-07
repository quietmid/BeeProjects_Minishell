/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:00:15 by jlu               #+#    #+#             */
/*   Updated: 2024/07/19 18:10:40 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_ismeta(char c)
{
	if (c == 124 || c == 36 || c == 60 || c == 62)
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

char	*find_end(char *str)
{
	while (*str != '\0' && !ft_ismeta(*str) && !ft_isspace(*str))
		str++;
	return (str);
}

int	ft_arr_len(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		x++;
	}
	return (x);
}
