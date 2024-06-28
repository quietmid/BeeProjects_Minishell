/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:55:45 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/28 21:05:47 by pbumidan         ###   ########.fr       */
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
	if (ft_arr_len(data->token[0].cmd) > 1)
	{
		x = 1;
		start = 1;
		while (data->token[0].cmd[x] && is_nflag(data->token[0].cmd[x]) == TRUE)
		{
			n = 1;
			x++;
			start = x;
		}
		while (data->token[0].cmd[start])
		{
			ft_putstr_fd(data->token[0].cmd[start], 1);
			if (start < (ft_arr_len(data->token[0].cmd) - 1))
				ft_putstr_fd(" ", 1);
			start++;
		}
	}
	if (n == 0) // || (n == 1 && ft_arr_len(data->token[0].cmd) == 2))
		ft_putstr_fd("\n", 1);
}

