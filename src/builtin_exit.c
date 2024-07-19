/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:22:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/19 15:33:17 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	convert_code(t_data *data, char *str)
{
	int	num;

	num = ft_atoi(str);
	while (num > 255)
	{
		num = (num - 256);
	}
	data->status = num;
}

static int	is_digit(t_data *data, char *str)
{
	int	x;

	(void)data;
	x = 0;
	while (str[x])
	{
		if (ft_isdigit(str[x]) == 0)
			return (FALSE);
		x++;
	}
	return (TRUE);
}

static void	exit_message(t_data *data, char *var, int c)
{
	if (c == 1)
	{
		if (data->cmd_count == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell-8.8$: ", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	if (c == 2)
	{
		if (data->cmd_count == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell-8.8$: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
}

void	run_exit(t_data *data, int x)
{
	if (ft_arr_len(data->token[x].cmd) > 1)
	{
		if (is_digit(data, data->token[x].cmd[1]) == FALSE)
		{
			exit_message(data, data->token[x].cmd[1], 2);
			data->status = 2;
		}
		else if (is_digit(data, data->token[x].cmd[1]) == TRUE
			&& ft_arr_len(data->token[x].cmd) == 2)
		{
			convert_code(data, data->token[x].cmd[1]);
			if (data->cmd_count == 1)
				ft_putstr_fd("exit\n", 2);
		}
		else
		{
			exit_message(data, NULL, 1);
			data->status = 1;
			return ;
		}
	}
	free_data_all(data, 0);
	exit(data->status);
}
