/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:55:45 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/12 14:59:12 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* check validity of echo's -n flag 
*/
int	is_nflag(char *str)
{
	int	x;

	x = 0;
	if (str[x] == '-')
	{
		x++;
		while (str[x])
		{
			if (str[x] != 'n')
				return (FALSE);
			x++;
		}
		return (TRUE);
	}
	return (FALSE);
}

/*
* execute builtin command echo (-n)
*/
void	run_echo(t_data *data)
{
	int	x;
	int	n;
	int	start;

	n = 0;
	if (ft_arr_len(data->line) > 1)
	{
		x = 1;
		start = 1;
		while (data->line[x] && is_nflag(data->line[x]) == TRUE)
		{
			n = 1;
			x++;
			start = x;
		}
		while (data->line[start])
		{
			ft_putstr_fd(data->line[start], 2);
			if (start < (ft_arr_len(data->line) - 1))
				ft_putstr_fd(" ", 2);
			start++;
		}
	}
	if (n == 0 || (n == 1 && ft_arr_len(data->line) == 2))
		ft_putstr_fd("\n", 2);
}

