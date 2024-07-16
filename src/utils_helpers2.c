/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:30:25 by jlu               #+#    #+#             */
/*   Updated: 2024/07/16 14:37:30 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_whitespace(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	skip_whitespace2(char *str, int i)
{
	while (!ft_isspace(str[i]) && !ft_isredir(str[i]) && str[i])
		i++;
	return (i);
}
