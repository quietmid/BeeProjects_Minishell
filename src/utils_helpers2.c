/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:30:25 by jlu               #+#    #+#             */
/*   Updated: 2024/07/19 18:15:25 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *str, int i)
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

int	check_token(t_data *data)
{
	if (data->token != NULL)
	{
		if (!here_doc(data))
			return (0);
		if (data->cmd_count == 1 && data->token[0].cmd == NULL)
			return (0);
	}
	return (1);
}
