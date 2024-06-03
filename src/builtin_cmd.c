/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:55:45 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/03 20:41:44 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* execute builtin command echo (-n)
*/
void	run_echo(t_data *data)
{
	int	x;
	int	n;
	int	start;

	n = 0;
	x = 1;
	start = 1;
	if (ft_strncmp(data->line[x], "-n", 2) == 0)
	{
		n = 1;
		start++;
		x++;
	}
	while (data->line[x])
	{
		if (x > start && x < ft_arrlen(data->line))
			ft_putstr_fd(" ", 2);
		ft_putstr_fd(data->line[x], 2);
		x++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 2);
}

/*
* execute builtin pwd
*/
void	run_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 2);
    ft_putstr_fd("\n", 2);
}
