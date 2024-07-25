/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:30:25 by jlu               #+#    #+#             */
/*   Updated: 2024/07/25 16:46:24 by jlu              ###   ########.fr       */
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
		if (data->cmd_count == 1 && data->token[0].cmd == NULL
			&& data->token[0].redir == NULL)
			return (0);
	}
	return (1);
}

void	signal_d(void)
{
	if (isatty(0))
		ft_putendl_fd("exit", 2);
	exit (0);
}

int	ft_isexp(char c)
{
	if (c == '_')
		return (1);
	else if (c == '?')
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isquote(c))
		return (1);
	else if (ft_isspace(c))
		return (0);
	else
		return (0);
}
